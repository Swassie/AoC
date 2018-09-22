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
	std::vector< std::array< int, 3 > > numbers;
	std::vector< std::vector< size_t > > distances;
	size_t xSize{ 0 }, ySize{ 0 };
	size_t x{ 0 }, y{ 0 };

	while( std::getline( fileStream, tempString ) ) {
		xSize = tempString.size();
		x = 0;
		for( char c : tempString ) {
			if( std::isdigit( c ) ) {
				numbers.push_back( { c - '0', x, y } );
			}
			map.push_back( c );
			++x;
		}
		++y;
	}
	ySize = y;

	for( int i{ 0 }; i < numbers.size(); ++i ) {
		distances.push_back( std::vector< size_t >( numbers.size() ) );
	}

	std::sort( numbers.begin(), numbers.end(), [] (  const std::array< int, 3 > &a, const std::array< int, 3 > &b ) {
		return a[ 0 ] < b[ 0 ];
	});

	while( numbers.size() > 1 ) {
		std::map< std::array< int, 2 >, uint8_t > closedSet;
		std::map< std::array< int, 2 >, size_t > openSet;
		openSet[ { numbers[ 0 ][ 1 ], numbers[ 0 ][ 2 ] } ] = 0;
		State current;

		int from{ numbers[ 0 ][ 0 ] };
		numbers.erase( numbers.begin() );

		std::vector< int > lookingFor;
		for( std::array< int, 3 > &array : numbers ) {
			lookingFor.push_back( array[ 0 ] );
		}

		while ( openSet.size()) {
			auto lowestIt = openSet.begin();
			for ( auto it = openSet.begin(); it != openSet.end(); ++it ) {
				if ( it->second < lowestIt->second ) {
					lowestIt = it;
				}
			}
			current = { lowestIt->first[ 0 ], lowestIt->first[ 1 ], lowestIt->second };

			char c{ map[ current.x + current.y * xSize ] };
			if( std::isdigit( c ) ) {
				auto it = std::find( lookingFor.begin(), lookingFor.end(), c - '0' );
				if( it != lookingFor.end() ) {
					distances[ from ][ *it ] = current.tentativeScore;
					distances[ *it ][ from ] = current.tentativeScore;
					lookingFor.erase( it );
				}
			}

			if ( lookingFor.empty() ) {
				break;
			}

			openSet.erase( lowestIt );
			closedSet[ { current.x, current.y } ] = 1;

			std::vector< State > neighbours{ current.getNeighbours( map, xSize ) };
			for ( State neighbour : neighbours ) {
				if ( closedSet.count( { neighbour.x, neighbour.y } )) {
					continue;
				}

				size_t tentativeScore{ current.tentativeScore + 1 };

				auto it = openSet.find( { neighbour.x, neighbour.y } );

				if ( it == openSet.end()) {
					openSet[ { neighbour.x, neighbour.y } ] = tentativeScore;
				}
				else if ( tentativeScore >= it->second ) {
					continue;
				}
				else {
					it->second = tentativeScore;
				}
			}
		}
	}

	std::vector< int > path;
	for( int i{ 1 }; i < distances.size(); ++i ) {
		path.push_back( i );
	}

	size_t minCost{ ( size_t )-1 };
	do {
		size_t cost{ distances[ 0 ][ path[ 0 ] ] };
		for( int i{ 0 }; i < ( path.size() - 1 ); ++i ) {
			cost += distances[ path[ i ] ][ path[ i + 1 ] ];
		}
		cost += distances[ path.back() ][ 0 ];
		minCost = cost < minCost ? cost : minCost;
	} while( std::next_permutation( path.begin(), path.end() ));

	std::cout << "Least cost: " << minCost << std::endl;

	return 0;
}