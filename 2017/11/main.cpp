#include <iostream>
#include <fstream>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string direction;
	int x{ 0 }, y{ 0 }, z{ 0 };
	int maxDist{ 0 };

	while( std::getline( fileStream, direction, ',' )) {
		if( direction.back() == '\n' ) {
			direction.pop_back();
		}
		if( direction == "n" ) {
			++y;
			--z;
		}
		else if( direction == "ne" ) {
			++x;
			--z;
		}
		else if( direction == "se" ) {
			++x;
			--y;
		}
		else if( direction == "s" ) {
			--y;
			++z;
		}
		else if( direction == "sw" ) {
			--x;
			++z;
		}
		else if( direction == "nw" ) {
			--x;
			++y;
		}
		int dist{ ( std::abs( x ) + std::abs( y ) + std::abs( z )) / 2 };
		maxDist = dist > maxDist ? dist : maxDist;
	}

	std::cout << "Distance: " << ( std::abs( x ) + std::abs( y ) + std::abs( z )) / 2 << std::endl;
	std::cout << "Max distance: " << maxDist << std::endl;
	return 0;
}