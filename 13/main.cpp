#include <iostream>
#include <vector>
#include "Node.h"

int main() {

	Node initialNode{ 1, 1 };
	initialNode.tentativeDist = 0;
	Node curNode( initialNode );
	std::vector< Node > visitedSet, unvisitedSet{ curNode };

	while( true ) {
		std::vector< Node > neighbours{ curNode.findOpenNeighbours() };

		for( Node node : neighbours ) {
			auto it = std::find_if( visitedSet.begin(), visitedSet.end(), [ node ] ( Node &other ) {
				return node.getCoords() == other.getCoords();
			});

			if( it != visitedSet.end()) {
				continue;
			}

			it = std::find_if( unvisitedSet.begin(), unvisitedSet.end(), [ node ] ( Node &other ) {
				return node.getCoords() == other.getCoords();
			});

			if( it == unvisitedSet.end()) {
				node.tentativeDist = curNode.tentativeDist + 1;
				unvisitedSet.push_back( node );
				continue;
			}

			if( curNode.tentativeDist + 1 < it->tentativeDist ) {
				it->tentativeDist = curNode.tentativeDist + 1;
			}
		}

		visitedSet.push_back( curNode );
		unvisitedSet.erase( unvisitedSet.begin() );

		if( curNode.getCoords() == std::pair< size_t, size_t >{ 31, 39 } ) {
			break;
		}

		std::sort( unvisitedSet.begin(), unvisitedSet.end(), [] ( const Node &node1, const Node &node2 ) {
			return node1.tentativeDist < node2.tentativeDist;
		});

		curNode = unvisitedSet.front();
	}

	std::cout << "Number of steps: " << curNode.tentativeDist << std::endl;

	size_t locationCount{ 0 };
	for( Node node : visitedSet ) {
		if( node.tentativeDist <= 50 ) {
			locationCount++;
		}
	}

	std::cout << "Number of locations reachable within 50 steps: " << locationCount;
	return 0;
}