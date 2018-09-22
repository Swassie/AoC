#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

class Vector
{
public:
	Vector() = default;
	Vector(long int x, long int y, long int z)
		: m_x(x), m_y(y), m_z(z) {}

	bool operator==(const Vector& v) const
	{
		return m_x == v.m_x && m_y == v.m_y && m_z == v.m_z;
	}

	double getMagnitude() const
	{
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	long int m_x, m_y, m_z;
};

class Particle
{
public:
	Particle() = default;
	Particle(Vector p, Vector v, Vector a, size_t nr)
		: m_p(p), m_v(v), m_a(a), m_nr(nr) {}
	Vector m_p, m_v, m_a;
	size_t m_nr;
};

Vector getCoords(std::istringstream& stream)
{
	Vector v;
	long int i;
	stream >> i;
	v.m_x = i;
	stream.ignore();

	stream >> i;
	v.m_y = i;
	stream.ignore();

	stream >> i;
	v.m_z = i;

	return v;
}

int main()
{
	std::ifstream inputStream("../input.txt");
	std::vector<Particle> particles;
	std::string tempStr;
	size_t particleNr{0};

	while(std::getline(inputStream, tempStr))
	{
		std::istringstream stream(tempStr);
		stream.ignore(3);
		Vector p{getCoords(stream)};
		stream.ignore(6);
		Vector v{getCoords(stream)};
		stream.ignore(6);
		Vector a{getCoords(stream)};

		particles.emplace_back(p, v, a, particleNr++);
	}

	Particle closestParticle{particles[0]};

	for(Particle particle : particles)
	{
		if(particle.m_a.getMagnitude() < closestParticle.m_a.getMagnitude())
		{
			closestParticle = particle;
		}
	}

	std::cout << "Closest particle: " << closestParticle.m_nr << std::endl;

	size_t iterCnt{0};
	while(true)
	{
		std::set<size_t> collisionNr;

		// Find collisions
		for(std::vector<Particle>::iterator it1{particles.begin()}; it1 < particles.end(); ++it1)
		{
			for(std::vector<Particle>::iterator it2{it1 + 1}; it2 < particles.end(); ++it2)
			{
				if(it1->m_p == it2->m_p)
				{
					collisionNr.insert(it1->m_nr);
					collisionNr.insert(it2->m_nr);
				}
			}
		}

		// Remove colliding particles
		for(size_t nr : collisionNr)
		{
			for(std::vector<Particle>::iterator it{particles.begin()}; it < particles.end(); ++it)
			{
				if(it->m_nr == nr)
				{
					particles.erase(it);
					std::cout << "Collision detected at iteration " << iterCnt << ", " << particles.size() << " particles remaining." << std::endl;
					break;
				}
			}
		}

		// Update position and velocity
		for(Particle& p : particles)
		{
			p.m_v.m_x += p.m_a.m_x;
			p.m_v.m_y += p.m_a.m_y;
			p.m_v.m_z += p.m_a.m_z;
			
			p.m_p.m_x += p.m_v.m_x;
			p.m_p.m_y += p.m_v.m_y;
			p.m_p.m_z += p.m_v.m_z;
		}
		
		++iterCnt;
	}

	return 0;
}
