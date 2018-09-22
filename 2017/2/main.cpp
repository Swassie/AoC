#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::vector< int > row;
	std::string tempString;
	int checksum1{ 0 };
	int checksum2{ 0 };
	int number;

	while( std::getline( fileStream, tempString )) {
		std::istringstream rowStream{ tempString };
		row.clear();

		while( rowStream >> number ) {
			row.push_back( number );
		}

		int min{ *std::min_element( row.begin(), row.end())};
		int max{ *std::max_element( row.begin(), row.end())};
		checksum1 += max - min;

		for( std::vector< int >::iterator iter1{ row.begin() }; iter1 < row.end(); ++iter1 ) {
			for( std::vector< int >::iterator iter2{ iter1 + 1 }; iter2 < row.end(); ++iter2 ) {
				if( *iter1 % *iter2 == 0 ) {
					checksum2 += *iter1 / *iter2;
				}
				else if( *iter2 % *iter1 == 0 ) {
					checksum2 += *iter2 / *iter1;
				}
			}
		}
	}

	std::cout << "Checksum1: " << checksum1 << std::endl;
	std::cout << "Checksum2: " << checksum2 << std::endl;

	return 0;
}