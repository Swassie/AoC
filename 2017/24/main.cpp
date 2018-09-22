#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

size_t calculateStrength(const std::vector<std::pair<size_t, size_t>> &bridge)
{
	size_t strength{0};
	for(const std::pair<size_t, size_t> &pair : bridge)
	{
		strength += pair.first;
		strength += pair.second;
	}
	return strength;
}

void findStrongest(std::vector<std::pair<size_t, size_t>> &bridge,
                   std::vector<std::pair<size_t, size_t>> &components,
                   size_t lastPort,
                   size_t &maxStrength)
{
	for(auto it{components.begin()}; it < components.end(); ++it)
	{
		if(it->first == lastPort || it->second == lastPort)
		{
			bridge.push_back(*it);
			std::vector<std::pair<size_t, size_t>> newComponents{components};
			const size_t index(it - components.begin());
			newComponents.erase(newComponents.begin() + index);
			size_t newLastPort{it->first == lastPort ? it->second : it->first};

			findStrongest(bridge, newComponents, newLastPort, maxStrength);
			bridge.pop_back();
		}
	}

	size_t strength{calculateStrength(bridge)};
	if(strength > maxStrength)
	{
		maxStrength = strength;
	}
}

void findLongest(std::vector<std::pair<size_t, size_t>> &bridge,
                 std::vector<std::pair<size_t, size_t>> &components,
                 size_t lastPort,
                 size_t &maxStrength,
	             size_t &maxLength)
{
	for(auto it{components.begin()}; it < components.end(); ++it)
	{
		if(it->first == lastPort || it->second == lastPort)
		{
			bridge.push_back(*it);
			std::vector<std::pair<size_t, size_t>> newComponents{components};
			const size_t index(it - components.begin());
			newComponents.erase(newComponents.begin() + index);
			size_t newLastPort{it->first == lastPort ? it->second : it->first};

			findLongest(bridge, newComponents, newLastPort, maxStrength, maxLength);
			bridge.pop_back();
		}
	}

	if(bridge.size() > maxLength)
	{
		maxLength = bridge.size();
		maxStrength = calculateStrength(bridge);
	}
	else if(bridge.size() == maxLength)
	{
		size_t strength{calculateStrength(bridge)};
		if(strength > maxStrength)
		{
			maxStrength = strength;
		}
	}
}

int main()
{
	std::ifstream file{"../input.txt"};
	std::string tempString;
	std::vector<std::pair<size_t, size_t>> components, bridge;
	
	while(std::getline(file, tempString))
	{
		std::istringstream stream{tempString};
		size_t portA, portB;
		stream >> portA;
		stream.ignore();
		stream >> portB;
		
		components.emplace_back(portA, portB);
	}

	size_t maxStrength{0}, maxLength{0};

	findStrongest(bridge, components, 0, maxStrength);

	std::cout << "Max strength: " << maxStrength << std::endl;

	maxStrength = 0;
	findLongest(bridge, components, 0, maxStrength, maxLength);

	std::cout << "Max strength of longest bridge: " << maxStrength << std::endl;

	return 0;
}
