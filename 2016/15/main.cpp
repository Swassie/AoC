#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Disc.h"

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	std::vector< Disc > discs;
	size_t time{ 0 };

	while( std::getline( fileStream, tempString )) {
		std::istringstream inputStream{ tempString };

		inputStream.seekg( 6 );
		size_t discNr, positions, startPosition;
		inputStream >> discNr;
		inputStream >> tempString;
		inputStream >> positions;
		inputStream.ignore( 41 );
		inputStream >> startPosition;
		Disc disc{ discNr, positions, startPosition };
		discs.push_back( disc );
	}

	discs.push_back( { discs.size() + 1, 11, 0 });

	// Check if correctly aligned from start
	bool done = std::all_of( discs.begin(), discs.end(), [] ( const Disc &disc ) {
		return disc.correctAligned();
	});

	if( done ) {
		std::cout << "First time to press button: " << time;
		return 0;
	}

	// Sort to find the longest cycle
	std::sort( discs.begin(), discs.end(), [] ( const Disc &a, const Disc &b ) {
		return a.positionCount > b.positionCount;
	});

	size_t cycle{ discs.front().positionCount };
	size_t cycleAdjustment{ cycle - (( discs.front().position + discs.front().discNr ) % cycle ) };

	// Align the biggest disc correctly
	std::for_each( discs.begin(), discs.end(), [ cycleAdjustment ] ( Disc &disc ) { disc.tick( cycleAdjustment ); });
	time += cycleAdjustment;

	done = std::all_of( discs.begin(), discs.end(), [] ( const Disc &disc ) {
		return disc.correctAligned();
	});

	while( !done ) {
		std::for_each( discs.begin(), discs.end(), [ cycle ] ( Disc &disc ) { disc.tick( cycle ); });
		time += cycle;
		done = std::all_of( discs.begin(), discs.end(), [] ( const Disc &disc ) {
			return disc.correctAligned();
		});
	}

	std::cout << "First time to press button: " << time;

	return 0;
}