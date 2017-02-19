
#include <algorithm>
#include "State.h"

size_t State::estimateCost() const {
	//return ( numbers.size() - std::count( numbers.begin(), numbers.end(), 1 ));
	return 0;
}

std::vector< State > State::getNeighbours( std::vector< char > &map, size_t xSize ) const {
	std::vector< State > neighbours;

	char c{ map[ x + ( y - 1 ) * xSize ] };
	if( c != '#' ) {
		State newState( *this );
		newState.y--;
		if( c != '.' && c != '0' ) {
			newState.numbers |= static_cast< uint32_t >( pow( 2, c - '1' ) );
			//newState.numbers[ c - '1' ] = 1;
		}
		neighbours.push_back( newState );
	}

	c = map[ x + ( y + 1 ) * xSize ];
	if( c != '#' ) {
		State newState( *this );
		newState.y++;
		if( c != '.' && c != '0' ) {
			newState.numbers |= static_cast< uint32_t >( pow( 2, c - '1' ) );
			//newState.numbers[ c - '1' ] = 1;
		}
		neighbours.push_back( newState );
	}

	c = map[ ( x - 1 ) + y * xSize ];
	if( c != '#' ) {
		State newState( *this );
		newState.x--;
		if( c != '.' && c != '0' ) {
			newState.numbers |= static_cast< uint32_t >( pow( 2, c - '1' ) );
			//newState.numbers[ c - '1' ] = 1;
		}
		neighbours.push_back( newState );
	}

	c = map[ ( x + 1 ) + y * xSize ];
	if( c != '#' ) {
		State newState( *this );
		newState.x++;
		if( c != '.' && c != '0' ) {
			newState.numbers |= static_cast< uint32_t >( pow( 2, c - '1' ) );
			//newState.numbers[ c - '1' ] = 1;
		}
		neighbours.push_back( newState );
	}
	return neighbours;
}
