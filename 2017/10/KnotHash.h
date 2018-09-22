#pragma once

#include <string>
#include <vector>

class KnotHash {
public:
	static std::string hash( std::string input, int rounds );
	static std::vector< int > sparseHash( const std::vector< int >& lengths, int rounds );
};
