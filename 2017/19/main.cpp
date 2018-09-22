#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::ifstream inputStream("../input.txt");
	std::vector<std::string> map;
	std::string tempStr;

	while(std::getline(inputStream, tempStr))
	{
		map.push_back(tempStr);
	}

	size_t x{map[0].find('|')};
	size_t y{0};
	enum class Axis { horizontal, vertical };
	Axis axis{ Axis::vertical };
	int direction{1}; // Direction along the axis, 1 or -1.

	std::string letters;
	size_t steps{0};

	while(map[y][x] != ' ')
	{
		switch(map[y][x])
		{
		case '|':
			if(axis == Axis::vertical)
			{
				y += direction;
			}
			else
			{
				x += direction;
			}
			break;
		case '-':
			if(axis == Axis::horizontal)
			{
				x += direction;
			}
			else
			{
				y += direction;
			}
			break;
		case '+':
			if(axis == Axis::horizontal)
			{
				axis = Axis::vertical;
				if(y > 0 && map[y - 1][x] == '|')
				{
					direction = -1;
				}
				else if(y < map.size() - 1 && map[y + 1][x] == '|')
				{
					direction = 1;
				}
				else
				{
					assert(false);
				}
				y += direction;
			}
			else
			{
				axis = Axis::horizontal;
				if(x > 0 && map[y][x - 1] == '-')
				{
					direction = -1;
				}
				else if(x < map[y].size() - 1 && map[y][x + 1] == '-')
				{
					direction = 1;
				}
				else
				{
					assert(false);
				}
				x += direction;
			}
			break;
		default:
			letters.push_back(map[y][x]);
			
			if(axis == Axis::vertical)
			{
				y += direction;
			}
			else
			{
				x += direction;
			}

			break;
		}
		++steps;
	}

	std::cout << "Letters: " << letters << std::endl;
	std::cout << "Steps: " << steps << std::endl;

	return 0;
}
