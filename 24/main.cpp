#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "State.h"

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	std::vector< char > map;
	size_t xSize{ 0 }, ySize{ 0 };

	while( std::getline( fileStream, tempString ) ) {
		xSize = tempString.size();
		for( char c : tempString ) {
			map.push_back( c );
		}
	}
	ySize = map.size() / xSize;

	size_t numberCount{ std::count_if( map.begin(), map.end(), [] ( char c ) {
		return std::isdigit( c );
	}) - 1 };

	long index{ std::find( map.begin(), map.end(), '0' ) - map.begin() };
	int xStart{ index % xSize }, yStart{ index / xSize };

	//std::vector< State > closedSet, openSet;
	std::map< std::array< int, 3 >, uint8_t > closedSet;
	std::map< std::array< int, 3 >, State > openSet;
	openSet[ { xStart, yStart, 0 } ] = { xStart, yStart, 0, numberCount, 0 };
	State current{ xStart, yStart, 0, 0, 0 };

	while( openSet.size() ) {
		auto lowestIt = openSet.begin();
		for( auto it = openSet.begin(); it != openSet.end(); ++it ) {
			if( it->second.fScore < lowestIt->second.fScore ) {
				lowestIt = it;
			}
		}

		current = lowestIt->second;
		//std::cout << current.estimateCost() << std::endl;
		//std::cout << closedSet.size() << "  " << openSet.size() << std::endl;
		if( current.numbers == static_cast< uint32_t >( pow( 2, numberCount ) - 1 ) &&
				map[ current.x + current.y * xSize ] == '0' ) {
			std::cout << "Least number of steps: " << current.gScore << std::endl;
			return 0;
		}

		openSet.erase( lowestIt );
		closedSet[ { current.x, current.y, current.numbers } ] = 1;

		std::vector< State > neighbours{ current.getNeighbours( map, xSize )};
		for( State neighbour : neighbours ) {
			if( closedSet.count({ neighbour.x, neighbour.y, neighbour.numbers })) {
				continue;
			}

			size_t tentativeGScore{ current.gScore + 1 };

			auto it = openSet.find({ neighbour.x, neighbour.y, neighbour.numbers });

			if( it == openSet.end() ) {
				openSet[{ neighbour.x, neighbour.y, neighbour.numbers }] = neighbour;
				it = openSet.find({ neighbour.x, neighbour.y, neighbour.numbers });
			}
			else if( tentativeGScore >= it->second.gScore ) {
				continue;
			}

			it->second.gScore = tentativeGScore;
			it->second.fScore = it->second.gScore;
		}
	}

	std::cout << "Search failed :( " << std::endl;

	return 0;
}