
#include "State.h"

std::vector< State > State::getNeighbours( std::vector< char > &map, size_t xSize ) const {
	std::vector< State > neighbours;
	State newState( *this );

	char c{ map[ x + ( y - 1 ) * xSize ] };
	if( c != '#' ) {
		newState.y--;
		neighbours.push_back( newState );
		newState.y++;
	}

	c = map[ x + ( y + 1 ) * xSize ];
	if( c != '#' ) {
		newState.y++;
		neighbours.push_back( newState );
		newState.y--;
	}

	c = map[ ( x - 1 ) + y * xSize ];
	if( c != '#' ) {
		newState.x--;
		neighbours.push_back( newState );
		newState.x++;
	}

	c = map[ ( x + 1 ) + y * xSize ];
	if( c != '#' ) {
		newState.x++;
		neighbours.push_back( newState );
	}
	return neighbours;
}
