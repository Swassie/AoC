#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <iomanip>
#include "KnotHash.h"

int main() {

	std::ifstream inputStream{ "../input.txt" };
	std::string tempString;

	std::getline( inputStream, tempString );
	std::istringstream intStream{ tempString };

	std::vector< int > lengths;
	int length;

	while( intStream >> length ) {
		intStream.ignore();
		lengths.push_back( length );
	}

	std::vector< int > part1{ KnotHash::sparseHash( lengths, 1 )};

	std::cout << "Result: " << part1[ 0 ] * part1[ 1 ] << std::endl;

	std::cout << KnotHash::hash( tempString, 64 ) << std::endl;

	return 0;
}
