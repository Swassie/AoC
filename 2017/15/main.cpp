#include <cstdint>
#include <iostream>

int main()
{
	constexpr uint64_t aInput{ 512 };
	constexpr uint64_t bInput{ 191 };
	uint64_t aValue{ aInput };
	uint64_t bValue{ bInput };
	int matchCnt{ 0 };

	for( int i{ 0 }; i < 40000000; ++i )
	{
		aValue = aValue * 16807 % 2147483647;
		bValue = bValue * 48271 % 2147483647;

		if(( aValue & 0xFFFF ) == ( bValue & 0xFFFF ))
		{
			++matchCnt;
		}
	}

	std::cout << "Nr of matches in part 1: " << matchCnt << std::endl;

	aValue = aInput;
	bValue = bInput;
	matchCnt = 0;

	for( int i{ 0 }; i < 5000000; ++i )
	{
		do
		{
			aValue = aValue * 16807 % 2147483647;			
		} while( aValue % 4 != 0 );

		do
		{
			bValue = bValue * 48271 % 2147483647;			
		} while( bValue % 8 != 0 );

		if(( aValue & 0xFFFF ) == ( bValue & 0xFFFF ))
		{
			++matchCnt;
		}
	}

	std::cout << "Nr of matches in part 2: " << matchCnt << std::endl;
	
	return 0;
}
