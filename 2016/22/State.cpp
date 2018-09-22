
#include <iostream>
#include <cmath>
#include <limits>
#include "State.h"

void State::moveData( int xSrc, int ySrc, int xDest, int yDest ) {
	Node &a( nodes[ ySrc + xSrc * ySize ] );
	Node &b( nodes[ yDest + xDest * ySize ] );

	if( xSrc == goalData.first && ySrc == goalData.second ) {
		goalData.first = xDest;
		goalData.second = yDest;
	}

	b.used += a.used;
	b.avail = b.size - b.used;
	a.used = 0;
	a.avail = a.size;
	moves.push_back( { xSrc, ySrc, xDest, yDest });
	calculateState();
}

const Node& State::getNode( int x, int y ) const {
	return nodes[ y + x * ySize ];
}

void State::calculateState() {
	state.clear();
	for ( Node n : nodes ) {
		if ( n.used == 0 ) {
			continue;
		}
		if ( n.y != 0 && n.used <= getNode( n.x, n.y - 1 ).avail ) {
			state.push_back( { n.x, n.y, n.x, n.y - 1 } );
		}
		if ( n.y + 1 < ySize && n.used <= getNode( n.x, n.y + 1 ).avail ) {
			state.push_back( { n.x, n.y, n.x, n.y + 1 } );
		}
		if ( n.x != 0 && n.used <= getNode( n.x - 1, n.y ).avail ) {
			state.push_back( { n.x, n.y, n.x - 1, n.y } );
		}
		if ( n.x + 1 < xSize && n.used <= getNode( n.x + 1, n.y ).avail ) {
			state.push_back( { n.x, n.y, n.x + 1, n.y } );
		}
	}
}

std::vector< State > State::getValidMoves() const {
	std::vector< State > validMoves;

	for( Node n : nodes ) {
		if ( n.used == 0 ) {
			continue;
		}
		if( n.y != 0 && n.used <= getNode( n.x, n.y - 1 ).avail ) {
			State newState( *this );
			newState.moveData( n.x, n.y, n.x, n.y - 1 );
			validMoves.push_back( newState );
		}
		if( n.y + 1 < ySize && n.used <= getNode( n.x, n.y + 1 ).avail ) {
			State newState( *this );
			newState.moveData( n.x, n.y, n.x, n.y + 1 );
			validMoves.push_back( newState );
		}
		if( n.x != 0 && n.used <= getNode( n.x - 1, n.y ).avail ) {
			State newState( *this );
			newState.moveData( n.x, n.y, n.x - 1, n.y );
			validMoves.push_back( newState );
		}
		if( n.x + 1 < xSize && n.used <= getNode( n.x + 1, n.y ).avail ) {
			State newState( *this );
			newState.moveData( n.x, n.y, n.x + 1, n.y );
			validMoves.push_back( newState );
		}
	}
	return validMoves;
}

size_t State::costEstimate() const {
	size_t goalDist{ static_cast< size_t >(( goalData.first + goalData.second ) * 5 ) };
	size_t emptyDist{ static_cast< size_t >( -1 ) };

	for( Node n : nodes ) {
		if( n.used == 0 ) {
			size_t dist{ static_cast< size_t >( abs( goalData.first - n.x ) + abs( goalData.second - n.y ) ) };
			emptyDist = dist < emptyDist ? dist : emptyDist;
		}
	}
	return goalDist + emptyDist;
}

void State::print() const {
	for( int y{ 0 }; y < ySize; ++y ) {
		std::cout << std::endl;
		for( int x{ 0 }; x < xSize; ++x ) {
			const Node n( getNode( x, y ) );
			if( goalData.first == x && goalData.second == y ) {
				std::cout << "G ";
			}
			else if( n.used == 0 ) {
				std::cout << "0 ";
			}
			else if( n.used < 100 ) {
				std::cout << ". ";
			}
			else {
				std::cout << "# ";
			}
		}
	}
	std::cout << std::endl << std::endl;
}

bool operator==( const State &a, const State &b ) {
	return a.goalData == b.goalData && a.state == b.state;
}