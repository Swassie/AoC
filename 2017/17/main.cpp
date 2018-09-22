#include <list>
#include <iostream>

int main()
{
	int input{324};
	std::list<int> buffer;
	int curPos{0};
	
	buffer.push_back(0);

	for(int i{1}; i < 2018; ++i)
	{
		curPos = (curPos + input) % buffer.size();
		std::list<int>::iterator it{std::next(buffer.begin(), curPos + 1)};
		buffer.insert(it, i);
		++curPos;
	}

	std::cout << *(std::next(buffer.begin(), (curPos + 1) % buffer.size())) << std::endl;
	
	int after0{*(std::next(buffer.begin(), 1))};
	size_t size{buffer.size()};

	for(int i{2018}; i < 50000001; ++i)
	{
		curPos = (curPos + input) % size;
		if(curPos == 0)
		{
			after0 = i;
		}
		++size;
		++curPos;
	}

	std::cout << after0 << std::endl;

	return 0;
}
