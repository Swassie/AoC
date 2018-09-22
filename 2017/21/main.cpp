#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Square
{
public:
	Square(const std::string &str)
		: m_str(str) {}

	bool operator==(const Square &other) const
	{
		return m_str == other.m_str;
	}

	size_t size() const
	{
		return std::sqrt(m_str.size());
	}

	size_t getOnCount() const
	{
		return std::count(m_str.begin(), m_str.end(), '#');
	}

	std::vector<Square> split() const
	{
		std::vector<Square> squares;

		bool even{size() % 2 == 0};
		size_t squaresPerSide{even ? size() / 2 : size() / 3};
		size_t squareSize{even ? 2u : 3u};

		for(size_t squareY{0}; squareY < squaresPerSide; ++squareY)
		{
			for(size_t squareX{0}; squareX < squaresPerSide; ++squareX)
			{
				std::string tempStr;
				for(size_t y{0}; y < squareSize; ++y)
				{
					for(size_t x{0}; x < squareSize; ++x)
					{
						tempStr += m_str[squareY * squareSize * squareSize * squaresPerSide +
										 squareX * squareSize +
										 y * squareSize * squaresPerSide +
										 x];
					}
				}
				squares.emplace_back(tempStr);
			}
		}

		return squares;
	}

	void enhance(std::vector<std::pair<Square, Square>> &rules)
	{
		for(const Square &variation : getVariations())
		{
			for(const std::pair<Square, Square> &pair : rules)
			{
				if(variation == pair.first)
				{
					m_str = pair.second.m_str;
				}
			}
		}
	}

	static Square join(const std::vector<Square> &squares)
	{
		std::string temp(squares.size() * squares[0].m_str.size(), ' ');
		size_t squaresPerSide{static_cast<size_t>(std::sqrt(squares.size()))};
		size_t squareSize{squares[0].size()};

		for(size_t squareY{0}; squareY < squaresPerSide; ++squareY)
		{
			for(size_t squareX{0}; squareX < squaresPerSide; ++squareX)
			{
				for(size_t y{0}; y < squareSize; ++y)
				{
					for(size_t x{0}; x < squareSize; ++x)
					{
						temp[squareY * squareSize * squareSize * squaresPerSide +
							 squareX * squareSize +
							 y * squareSize * squaresPerSide +
							 x] = squares[squareY * squaresPerSide + squareX].m_str[y * squareSize + x];
					}
				}
			}
		}

		return Square{temp};
	}
	
private:
	void flip()
	{
		std::string temp{m_str};

		if(m_str.size() == 4)
		{
			m_str[0] = m_str[1];
			m_str[1] = temp[0];
			m_str[2] = m_str[3];
			m_str[3] = temp[2];
		}
		else if(m_str.size() == 9)
		{
			m_str[0] = m_str[2];
			m_str[2] = temp[0];
			m_str[3] = m_str[5];
			m_str[5] = temp[3];
			m_str[6] = m_str[8];
			m_str[8] = temp[6];
		}
		else
		{
			assert(false);
		}
	}

	void rotate()
	{
		std::string temp{m_str};
		
		if(m_str.size() == 4)
		{
			m_str[0] = temp[2];
			m_str[1] = temp[0];
			m_str[2] = temp[3];
			m_str[3] = temp[1];
		}
		else if(m_str.size() == 9)
		{
			m_str[0] = temp[6];
			m_str[1] = temp[3];
			m_str[2] = temp[0];
			m_str[3] = temp[7];
			m_str[5] = temp[1];
			m_str[6] = temp[8];
			m_str[7] = temp[5];
			m_str[8] = temp[2];
		}
		else
		{
			assert(false);
		}
	}
	
	std::vector<Square> getVariations() const
	{
		std::vector<Square> variations;
		Square temp{*this};

		variations.push_back(temp);
		temp.rotate();
		variations.push_back(temp);
		temp.rotate();
		variations.push_back(temp);
		temp.rotate();
		variations.push_back(temp);
		temp.rotate();
		temp.flip();
		variations.push_back(temp);
		temp.rotate();
		variations.push_back(temp);
		temp.rotate();
		variations.push_back(temp);
		temp.rotate();
		variations.push_back(temp);

		return variations;
	}
	
	std::string m_str;
};

int main()
{
	std::ifstream inputStream("../input.txt");
	std::vector<std::pair<Square, Square>> rules;
	std::string line;

	while(std::getline(inputStream, line))
	{
		size_t size{line.find('/')};
		size_t pos{0};
		std::string tempStr;

		for(size_t i{0}; i < size; ++i)
		{
			for(size_t j{0}; j < size; ++j)
			{
				tempStr += line[pos++];
			}
			++pos;
		}

		Square leftSquare(tempStr);

		pos += 3;
		tempStr.clear();

		for(size_t i{0}; i < size + 1; ++i)
		{
			for(size_t j{0}; j < size + 1; ++j)
			{
				tempStr.push_back(line[pos++]);
			}
			++pos;
		}

		Square rightSquare(tempStr);

		rules.push_back({leftSquare, rightSquare});
	}

	Square image(".#...####");

	for(size_t iterations{0}; iterations < 18; ++iterations)
	{
		std::vector<Square> squares{image.split()};

		for(Square &square : squares)
		{
			square.enhance(rules);
		}

		image = Square::join(squares);

		if(iterations == 4)
		{
			std::cout << image.getOnCount() << " pixels are on after 5 iterations." << std::endl;
		}
	}

	std::cout << image.getOnCount() << " pixels are on after 18 iterations." << std::endl;
	
	return 0;
}
