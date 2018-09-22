#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

std::string dance( const std::string &inputPrograms,
                   const std::vector<uint8_t> &danceMoves,
                   size_t reps )
{
	std::string programs{ inputPrograms };
	size_t size{ danceMoves.size() };

	for( size_t rep{ 0 }; rep < reps; ++rep )
	{
		for( size_t i{ 0 }; i < size; ++i )
		{
			switch( danceMoves[i] )
			{
			case 's':
			{
				std::rotate( programs.rbegin(),
				             programs.rbegin() + danceMoves[i + 1],
				             programs.rend() );
				++i;
				break;
			}
			case 'x':
			{
				std::swap( programs[danceMoves[i + 1]],
				           programs[danceMoves[i + 2]] );
				i += 2;
				break;
			}
			case 'p':
			{
				std::swap( *std::find( programs.begin(), programs.end(), static_cast<char>(danceMoves[i + 1])),
				           *std::find( programs.begin(), programs.end(), static_cast<char>(danceMoves[i + 2])));
				i += 2;
				break;
			}
			}
		}
	}

	return programs;
}

int main()
{
	std::ifstream inputStream( "../input.txt" );
	const std::string initPrograms{ "abcdefghijklmnop" };
	std::vector<uint8_t> danceMoves;
	std::string tempStr;

	while( std::getline( inputStream, tempStr, ',' ))
	{
		std::istringstream danceMove{ tempStr };
		char type;
		danceMove >> type;
		danceMoves.push_back( type );

		switch( type )
		{
		case 's':
		{
			int num;
			danceMove >> num;
			danceMoves.push_back(num);
			break;
		}
		case 'x':
		{
			int a, b;
			danceMove >> a;
			danceMove.ignore();
			danceMove >> b;
			danceMoves.push_back(a);
			danceMoves.push_back(b);
			break;
		}
		case 'p':
		{
			char a, b;
			danceMove >> a;
			danceMove.ignore();
			danceMove >> b;
			danceMoves.push_back(a);
			danceMoves.push_back(b);
			break;
		}
		}
	}
	std::string programs{ initPrograms };
	int cycle{ -1 };

	programs = dance( programs, danceMoves, 1 );
	std::cout << "Program order after 1 dance: " << programs << std::endl;

	for( int i = 1;; ++i )
	{
		if( programs == initPrograms )
		{
			cycle = i;
			break;
		}
		
		programs = dance( programs, danceMoves, 1 );
	}
	
	programs = dance( initPrograms, danceMoves, 1000000000 % cycle );
	std::cout << "Program order after 1 billion dances: " << programs << std::endl;

	return 0;
}
