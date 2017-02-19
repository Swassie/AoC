
#ifndef INC_11_STATE_H
#define INC_11_STATE_H


#include <vector>
#include <numeric>
#include <cstddef>

class State {
public:
	inline bool validState( int floor1, int floor2 ) const;
	std::vector< State > getMoves() const;

	inline static size_t estimateCost( const std::vector< int > &locations ) {
		return locations.size() * 3 - std::accumulate( locations.begin(), locations.end(), 0 );
	}

	size_t fScore, gScore;
	std::vector< int > locations;
};

#endif //INC_11_STATE_H
