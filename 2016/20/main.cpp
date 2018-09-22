#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {

	using range_t = std::pair< unsigned int, unsigned int >;
	std::ifstream file{ "../input.txt" };
	std::string tempString;
	std::vector< range_t > validRanges{ { 0, 4294967295 } };

	while( std::getline( file, tempString )) {
		std::istringstream lineStream{ tempString };

		range_t range;
		lineStream >> range.first;
		lineStream.ignore();
		lineStream >> range.second;

		std::vector< range_t > newRanges;

		auto it = validRanges.begin();
		while( it != validRanges.end() ) {
			// Blocked range in valid range
			if( range.first > it->first && range.second < it->second ) {
				newRanges.push_back( { range.second + 1, it->second });
				it->second = range.first - 1;
			}
			// Blocked range surround the valid range
			else if( range.first <= it->first && range.second >= it->second ) {
				it = validRanges.erase( it );
				continue;
			}
			// Blocked range at start of valid range
			else if( range.first <= it->first && range.second >= it->first && range.second < it->second ) {
				it->first = range.second + 1;
			}
			// Blocked range at end of valid range
			else if( range.first > it->first && range.first <= it->second && range.second >= it->second ) {
				it->second = range.first - 1;
			}
			++it;
		}

		for( auto r : newRanges ) {
			validRanges.push_back( r );
		}
	}

	std::sort( validRanges.begin(), validRanges.end(), [] ( const range_t &a, const range_t &b ) {
		return a.first < b.first;
	});

	std::cout << "Lowest valid IP: " << validRanges.front().first << std::endl;

	size_t ipCount{ 0 };
	for( auto r : validRanges ) {
		ipCount += r.second - r.first + 1;
	}

	std::cout << "IP count: " << ipCount << std::endl;
	return 0;
}