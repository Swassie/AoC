
#include <iomanip>
#include <sstream>
#include "KnotHash.h"

std::vector< int > KnotHash::sparseHash( const std::vector< int >& lengths, int rounds ) {
	int currentPos{ 0 }, skipSize{ 0 };
	std::vector< int > list( 256 );

	for( int i{ 0 }; i < 256; ++i ) {
		list[ i ] = i;
	}

	for( int round{ 0 }; round < rounds; ++round ) {
		for( int length: lengths ) {

			for( int i{ 0 }; i < length / 2; ++i ) {
				std::swap( list[ ( currentPos + i ) % list.size() ],
				           list[ ( currentPos + length - 1 - i ) % list.size() ] );
			}

			currentPos = static_cast< int >(( currentPos + length + skipSize ) % list.size());
			++skipSize;
		}
	}
	return list;
}

std::string KnotHash::hash( std::string input, int rounds ) {
	std::vector< int > salt{ 17, 31, 73, 47, 23 };
	std::istringstream byteStream{ input };
	std::vector< int > lengths;
	char c;

	while( byteStream >> c ) {
		lengths.push_back( c );
	}
	lengths.insert( lengths.end(), salt.begin(), salt.end());

	std::vector< int > sparse{ sparseHash( lengths, rounds )};
	std::vector< int > dense;

	for( int i{ 0 }; i < sparse.size() / 16; ++i ) {
		int XOR{ 0 };

		for( int j{ 0 }; j < 16; ++j ) {
			XOR ^= sparse[ i * 16 + j ];
		}
		dense.push_back( XOR );
	}

	std::stringstream hexStream;
	for( int& i: dense ) {
		hexStream << std::hex << std::setfill( '0' ) << std::setw( 2 ) << i;
	}

	return hexStream.str();
}
