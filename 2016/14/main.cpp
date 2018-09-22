#include <iostream>
#include <deque>
#include <unordered_map>
#include "md5.h"

std::string md5Hash( std::string salt, size_t index ) {
	static std::unordered_map< size_t , std::string > hashes;
	auto it = hashes.find( index );
	if( it != hashes.end() ) {
		return it->second;
	}
	std::string str{ salt + std::to_string( index )};
	for( size_t offset{ 0 }; offset < 2017; ++offset ) {
		str = md5( str );
	}
	hashes[ index ] = str;
	return str;
}

bool checkNext1000( std::string salt, size_t index, char c ) {
	for( size_t offset{ 1 }; offset < 1001; ++offset ) {
		std::string hash{ md5Hash( salt, index + offset )};
		std::deque< char > q{ 'x', 'x', 'x', 'x', 'x' };
		for( char c2 : hash ) {
			q.pop_front();
			q.push_back( c2 );
			if( c == q[0] && q[0] == q[1] && q[0] == q[2] && q[0] == q[3] && q[0] == q[4] ) {
				return true;
			}
		}
	}
	return false;
}

int main() {

	size_t index{0}, keyCount{0};
	std::string salt{"qzyelonm"};

	while( keyCount < 64 ) {
		std::string hash{ md5Hash( salt, index )};
		std::deque< char > q{ 'x', 'x', 'x' };

		for( char c : hash ) {
			q.pop_front();
			q.push_back( c );
			if( q[0] == q[1] && q[0] == q[2] ) {
				if( checkNext1000( salt, index, c )) {
					++keyCount;
					std::cout << "Index: " << std::to_string( index ) <<
					          "  Total #: " << std::to_string( keyCount ) << std::endl;
				}
				break;
			}
		}
		++index;
	}

	return 0;
}