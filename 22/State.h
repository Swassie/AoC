
#ifndef INC_22_STATE_H
#define INC_22_STATE_H

#include <vector>
#include <array>
#include "Node.h"

class State {
public:
	std::vector< Node > nodes;
	std::pair< int, int > goalData;
	size_t fScore, gScore, xSize, ySize;
	std::vector< std::array< int, 4 > > state;
	std::vector< std::array< int, 4 > > moves;

	void moveData( int xSrc, int ySrc, int xDest, int yDest );
	void calculateState();
	const Node& getNode( int, int ) const;
	std::vector< State > getValidMoves() const;
	size_t costEstimate() const;
	void print() const;
};

bool operator==( const State &a, const State &b );

#endif //INC_22_STATE_H
