
#include "State.h"

std::vector< State > State::getMoves() const {
	std::vector< State > moves;
	int currentFloor{ locations[ 0 ] };

	if( currentFloor < 3 ) {
		State candidate( *this );
		candidate.locations[ 0 ]++;
		for ( int i{ 1 }; i < locations.size(); ++i ) {
			if ( currentFloor != locations[ i ] ) {
				continue;
			}
			candidate.locations[ i ]++;
			for ( int j{ i + 1 }; j < locations.size(); ++j ) {
				if ( currentFloor != locations[ j ] ) {
					continue;
				}
				candidate.locations[ j ]++;
				// Check pair
				if ( candidate.validState( currentFloor, currentFloor + 1 )) {
					moves.push_back( candidate );
				}
				candidate.locations[ j ]--;
			}
			// Check single
			if ( moves.empty() && candidate.validState( currentFloor, currentFloor - 1 )) {
				moves.push_back( candidate );
			}
			candidate.locations[ i ]--;
		}
	}
	if( currentFloor > 0 ) {
		State candidate( *this );
		bool oneDown{ false };
		candidate.locations[ 0 ]--;
		for ( int i{ 1 }; i < locations.size(); ++i ) {
			if ( currentFloor != locations[ i ] ) {
				continue;
			}
			candidate.locations[ i ]--;
			// Check single
			if ( candidate.validState( currentFloor, currentFloor - 1 )) {
				moves.push_back( candidate );
				oneDown = true;
			}
			if( oneDown ){
				continue;
			}
			for ( int j{ i + 1 }; j < locations.size(); ++j ) {
				if ( currentFloor != locations[ j ] ) {
					continue;
				}
				candidate.locations[ j ]--;
				// Check pair
				if ( candidate.validState( currentFloor, currentFloor + 1 )) {
					moves.push_back( candidate );
				}
				candidate.locations[ j ]++;
			}
			candidate.locations[ i ]++;
		}
	}

	// Sort the location vectors, so equivalent moves will look the same.
	for( State &state : moves ) {
		bool changed{ true };
		size_t end{ state.locations.size() };
		while( changed ) {
			changed = false;
			for( size_t i{ 1 }; ( i + 3 ) < end; i += 2 ) {
				if( state.locations[ i ] < state.locations[ i + 2 ] ) {
					std::swap( state.locations[ i ], state.locations[ i + 2 ] );
					std::swap( state.locations[ i + 1 ], state.locations[ i + 3 ] );
					changed = true;
				}
				else if( state.locations[ i ] == state.locations[ i + 2 ] &&
						state.locations[ i + 1 ] < state.locations[ i + 3 ] ) {
					std::swap( state.locations[ i ], state.locations[ i + 2 ] );
					std::swap( state.locations[ i + 1 ], state.locations[ i + 3 ] );
					changed = true;
				}
			}
			end -= 2;
		}
	}
	return moves;
}

bool State::validState( int floor1, int floor2 ) const {
	for( int i{ 1 }; i < locations.size(); i += 2 ) {
		int mcFloorNr{ locations[ i ] };
		if( mcFloorNr != floor1 && mcFloorNr != floor2 || mcFloorNr == locations[ i + 1 ] ) {
			continue;
		}
		for( int j{ 2 }; j < locations.size(); j += 2 ) {
			if( mcFloorNr == locations[ j ] ) {
				return false;
			}
		}
	}
	return true;
}
