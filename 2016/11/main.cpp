#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <map>
#include <algorithm>
#include "State.h"

struct Score {
	size_t fScore, gScore;
};

void showPath( std::map< std::vector< int >, std::vector< int > > &trace, std::vector< int > current ) {
	std::vector< std::vector< int > > path{ current };
	while( trace.count( current )) {
		current = trace[ current ];
		path.push_back( current );
	}
	std::reverse( path.begin(), path.end() );

	for( auto vec : path ) {
		for( auto i : vec ) {
			std::cout << i << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	std::vector< std::pair< std::string, int > > equipment;

	for( size_t floorNr = 0; floorNr < 4; ++floorNr ) {
		std::getline( fileStream, tempString );
		std::istringstream floorStream{ tempString };
		while( floorStream >> tempString ) {
			if ( tempString == "a" ) {
				std::string type;
				floorStream >> type;
				floorStream >> tempString;
				if( tempString.back() == ',' || tempString.back() == '.' ) {
					tempString.pop_back();
				}
				if (tempString == "generator" || tempString == "microchip" ) {
					equipment.push_back( { type + tempString, floorNr } );
				}
			}
		}
	}

	std::sort( equipment.begin(), equipment.end(),
	           [] ( std::pair< std::string, int > a, std::pair< std::string, int > b ) {
		           return a.first < b.first;
	           }
	);

	std::vector< int > locations{ 0 };
	for( auto pair : equipment ) {
		locations.push_back( pair.second );
	}

	std::map< std::vector< int >, uint8_t > closedSet;
	std::map< std::vector< int >, Score > openSet;
	std::map< std::vector< int >, std::vector< int > > trace;
	openSet[ locations ] = { 0, 0 };
	State current;

	while( openSet.size() ) {
		auto lowestIt = openSet.begin();
		for( auto it = openSet.begin(); it != openSet.end(); ++it ) {
			if( it->second.fScore < lowestIt->second.fScore ) {
				lowestIt = it;
			}
		}

		current = { lowestIt->second.fScore, lowestIt->second.gScore, lowestIt->first };

		if( std::count( current.locations.begin(), current.locations.end(), 3 ) == current.locations.size() ) {
			//showPath( trace, current.locations );
			std::cout << "Least number of steps: " << current.gScore << std::endl;
			return 0;
		}

		openSet.erase( lowestIt );
		closedSet[ current.locations ] = 1;

		std::vector< State > neighbours{ current.getMoves() };
		for( State neighbour : neighbours ) {
			if( closedSet.count( neighbour.locations )) {
				continue;
			}

			size_t tentativeGScore{ current.gScore + 1 };

			auto it = openSet.find( neighbour.locations );

			if( it == openSet.end() ) {
				openSet[ neighbour.locations ] = { neighbour.fScore, neighbour.gScore };
				it = openSet.find( neighbour.locations );
			}
			else if( tentativeGScore >= it->second.gScore ) {
				continue;
			}

			//trace[ neighbour.locations ] = current.locations;
			it->second.gScore = tentativeGScore;
			it->second.fScore = it->second.gScore + State::estimateCost( it->first );
		}
	}

	std::cout << "Search failed :( " << std::endl;

	return 0;
}