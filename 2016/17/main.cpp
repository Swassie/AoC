#include <iostream>
#include <vector>
#include <algorithm>
#include "md5.h"

void goToNext( std::string key, int x, int y, std::vector< std::string > &validPaths) {
	if( x == 3 && y == 3 ) {
		validPaths.push_back( key );
		return;
	}
	else if( x < 0 || x > 3 || y < 0 || y > 3 ) {
		return;
	}
	std::string md5Hash{ md5( key ).substr( 0, 4 ) };

	for( int i{ 0 }; i < md5Hash.size(); ++i ) {
		char c{ md5Hash[ i ] };
		bool isOpen{ c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f'};

		if( !isOpen ) {
			continue;
		}

		switch( i ) {
			case 0:
				goToNext( key + "U", x, y - 1, validPaths );
				break;
			case 1:
				goToNext( key + "D", x, y + 1, validPaths );
				break;
			case 2:
				goToNext( key + "L", x - 1, y, validPaths );
				break;
			case 3:
				goToNext( key + "R", x + 1, y, validPaths );
				break;
			default:
				return;
		}
	}
}

int main() {

	const std::string input{ "vkjiggvb" };
	std::vector< std::string > validPaths;

	goToNext( input, 0, 0, validPaths );

	std::sort( validPaths.begin(), validPaths.end(), [] ( const std::string &a, const std::string &b ) {
		return a.size() < b.size();
	});

	std::cout << "# of paths: " << validPaths.size() << std::endl;
	std::cout << "Shortest path: " << validPaths.front().substr( input.size() ) << std::endl;
	std::cout << "Length of longest path: " << validPaths.back().substr( input.size() ).size() << std::endl;


	return 0;
}