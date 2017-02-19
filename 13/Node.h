
#ifndef INC_13_NODE_H
#define INC_13_NODE_H


#include <bitset>
#include <algorithm>

class Node {
public:
	Node( size_t x, size_t y ) : x( x ), y( y ), tentativeDist( std::numeric_limits< size_t >::max() ) {};
	std::vector< Node > findOpenNeighbours();
	std::pair< size_t, size_t > getCoords() const;

	size_t x, y, tentativeDist;
};


#endif //INC_13_NODE_H
