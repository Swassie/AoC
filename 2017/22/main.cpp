#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <utility>

constexpr int part{2};

int main()
{
	enum class State : uint8_t {Clean, Weakened, Infected, Flagged};
	std::ifstream inputStream("../input.txt");
	std::map<std::pair<int, int>, State> nodes;
	std::string line;
	int lineNr{0};
	std::pair<int, int> pos{0, 0};

	while(std::getline(inputStream, line))
	{
		for(size_t x{0}; x < line.size(); ++x)
		{
			if(line[x] == '#')
			{
				nodes[{x, lineNr}] = State::Infected;
			}
		}
		++lineNr;
		pos.first = line.size() / 2;
	}

	pos.second = lineNr / 2;

	// 0 = Up, 1 = Right, 2 = Down, 3 = Left
	int dir{0};
	size_t infectionCnt{0};

	constexpr size_t maxBursts{part == 1 ? 10000 : 10000000};

	for(size_t bursts{0}; bursts < maxBursts; ++bursts)
	{
		auto it{nodes.find(pos)};
		if constexpr(part == 1)
		{
			if(it != nodes.end())
			{
				dir = (dir + 1) % 4;
				nodes.erase(it);
			}
			else
			{
				dir = (dir + 3) % 4;
				nodes[pos] = State::Infected;
				++infectionCnt;
			}
		}
		else if constexpr(part == 2)
		{
			if(it != nodes.end())
			{
				if(it->second == State::Weakened)
				{
					it->second = State::Infected;
					++infectionCnt;
				}
				else if(it->second == State::Infected)
				{
					dir = (dir + 1) % 4;
					it->second = State::Flagged;
				}
				else if(it->second == State::Flagged)
				{
					dir = (dir + 2) % 4;
					nodes.erase(it);
				}
			}
			else
			{
				dir = (dir + 3) % 4;
				nodes[pos] = State::Weakened;
			}
		}

		switch(dir)
		{
		case 0:
			--pos.second;
			break;
		case 1:
			++pos.first;
			break;
		case 2:
			++pos.second;
			break;
		case 3:
			--pos.first;
			break;
		default:
			assert(false);
		}
	}

	std::cout << "Infected: " << infectionCnt << std::endl;

	return 0;
}
