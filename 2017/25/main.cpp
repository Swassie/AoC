#include <algorithm>
#include <deque>
#include <iostream>

void moveLeft(std::deque<uint8_t> &tape, std::deque<uint8_t>::iterator &cursor)
{
	if(cursor == tape.begin())
	{
		tape.push_front(0);
		cursor = tape.begin();
	}
	else
	{
		--cursor;
	}
}

void moveRight(std::deque<uint8_t> &tape, std::deque<uint8_t>::iterator &cursor)
{
	if(cursor + 1 == tape.end())
	{
		tape.push_back(0);
	}
	++cursor;
}

int main()
{
	std::deque<uint8_t> tape;
	char state{'A'};
	const size_t steps{12794428};

	tape.push_back(0);
	auto cursor{tape.begin()};

	for(size_t i{0}; i < steps; ++i)
	{
		if(state == 'A')
		{
			if(*cursor == 0)
			{
				*cursor = 1;
				moveRight(tape, cursor);
				state = 'B';
			}
			else
			{
				*cursor = 0;
				moveLeft(tape, cursor);
				state = 'F';
			}
		}
		else if(state == 'B')
		{
			if(*cursor == 0)
			{
				*cursor = 0;
				moveRight(tape, cursor);
				state = 'C';
			}
			else
			{
				*cursor = 0;
				moveRight(tape, cursor);
				state = 'D';
			}
		}
		else if(state == 'C')
		{
			if(*cursor == 0)
			{
				*cursor = 1;
				moveLeft(tape, cursor);
				state = 'D';
			}
			else
			{
				*cursor = 1;
				moveRight(tape, cursor);
				state = 'E';
			}
		}
		else if(state == 'D')
		{
			if(*cursor == 0)
			{
				*cursor = 0;
				moveLeft(tape, cursor);
				state = 'E';
			}
			else
			{
				*cursor = 0;
				moveLeft(tape, cursor);
				state = 'D';
			}
		}
		else if(state == 'E')
		{
			if(*cursor == 0)
			{
				*cursor = 0;
				moveRight(tape, cursor);
				state = 'A';
			}
			else
			{
				*cursor = 1;
				moveRight(tape, cursor);
				state = 'C';
			}
		}
		else if(state == 'F')
		{
			if(*cursor == 0)
			{
				*cursor = 1;
				moveLeft(tape, cursor);
				state = 'A';
			}
			else
			{
				*cursor = 1;
				moveRight(tape, cursor);
				state = 'A';
			}
		}
	}

	std::cout << "Diagnostic checksum: " << std::count(tape.begin(), tape.end(), 1) << std::endl;

	return 0;
}
