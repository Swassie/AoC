#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;

	std::getline( fileStream, tempString );
	std::istringstream rowStream{ tempString };
	std::vector< int > banks;
	int bank{ 0 };

	while( rowStream >> bank ) {
		banks.push_back( bank );
	}

	std::map< std::vector< int >, int > configs;
	int cycles{ 0 };

	while( configs.count( banks ) == 0 ) {
		configs[ banks ] = cycles;

		std::vector< int >::iterator iter{ std::max_element( banks.begin(), banks.end())};
		int blocks{ *iter };
		*iter = 0;
		for(; blocks > 0; --blocks ) {
			if( ++iter == banks.end() ) {
				iter = banks.begin();
			}
			++( *iter );
		}

		++cycles;
	}

	std::cout << "Cycles: " << cycles << std::endl;
	std::cout << "Loop size: " << cycles - configs[ banks ] << std::endl;

	return 0;
}