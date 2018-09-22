#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::vector< std::set< int >> groups;
	std::vector< std::vector< int >> unchecked;
	std::string tempString;
	int id;

	while( std::getline( fileStream, tempString )) {
		tempString.erase( std::remove( tempString.begin(), tempString.end(), ',' ), tempString.end());

		std::istringstream rowStream{ tempString };

		std::vector< int > group;
		rowStream >> id;
		group.push_back( id );
		rowStream.ignore( 5 );

		while( rowStream >> id ) {
			group.push_back( id );
		}
		unchecked.push_back( group );
	}

	while( !unchecked.empty() ) {
		bool changed{ false };
		int groupID{ unchecked[ 0 ][ 0 ]};
		groups.push_back({ groupID });
		do {
			changed = false;
			for( auto iter( unchecked.begin()); iter < unchecked.end(); ++iter ) {
				for( const int& a: *iter ) {
					if( a == groupID || groups.back().count( a )) {
						for( const int& b: *iter ) {
							groups.back().insert( b );
						}
						iter = unchecked.erase( iter );
						changed = true;
						break;
					}
				}
			}
		} while( changed );
	}

	std::cout << "Count in group 0: " << groups[ 0 ].size() << std::endl;
	std::cout << "Groups: " << groups.size() << std::endl;

	return 0;
}