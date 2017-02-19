#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Node.h"
#include "State.h"

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	std::vector< Node > nodes;

	// Skip the two first lines
	std::getline( fileStream, tempString );
	std::getline( fileStream, tempString );

	while( std::getline( fileStream, tempString )) {
		std::istringstream line{ tempString };
		line.ignore( 16 );

		int x, y;
		size_t size, used, avail;
		line >> x;
		line.ignore( 2 );
		line >> y;
		line >> size;
		line.ignore();
		line >> used;
		line.ignore();
		line >> avail;
		nodes.push_back( { x, y, size, used, avail });
	}

	size_t viablePairs{ 0 };

	for( Node a : nodes ) {
		for( Node b : nodes ) {
			if( a.used != 0 && ( a.x != b.x || a.y != b.y ) && a.used <= b.avail ) {
				++viablePairs;
			}
		}
	}

	std::cout << "Nr of viable pairs: " << viablePairs << std::endl;

	size_t xSize{ static_cast< size_t >( nodes.back().x ) + 1}, ySize{ static_cast< size_t >( nodes.back().y ) + 1 };

	std::vector< State > visited, unvisited;
	State current{ nodes, { xSize - 1, 0 }, static_cast< size_t >( -1 ), 0, xSize, ySize };
	current.calculateState();
	unvisited.push_back( current );

	while( !unvisited.empty() ) {
		std::sort( unvisited.begin(), unvisited.end(), [] ( const State &s1, const State &s2 ) {
			return s1.fScore < s2.fScore;
		});

		current = unvisited.front();

		if( current.goalData.first == 0 && current.goalData.second == 0 ) {
			break;
		}

		unvisited.erase( unvisited.begin() );
		visited.push_back( current );

		std::vector< State > validMoves( current.getValidMoves() );

		for( State &s : validMoves ) {
			auto it = std::find_if( visited.begin(), visited.end(), [ s ] ( State &other ) {
				return s == other;
			});

			if( it != visited.end()) {
				continue;
			}

			size_t tentativeGScore{ current.gScore + 1 };

			it = std::find_if( unvisited.begin(), unvisited.end(), [ s ] ( State &other ) {
				return s == other;
			});

			if( it == unvisited.end()) {
				unvisited.push_back( s );
				it = unvisited.end();
				--it;
			}
			else if( tentativeGScore >= it->gScore ) {
				continue;
			}

			it->gScore = tentativeGScore;
			it->fScore = it->gScore + it->costEstimate();
		}
	}

	std::cout << "Fewest # of steps: " << current.gScore << std::endl;

	return 0;
}