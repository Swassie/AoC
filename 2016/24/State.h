
#ifndef INC_24_STATE_H
#define INC_24_STATE_H


#include <vector>
#include <cstddef>

class State {
public:
	std::vector< State > getNeighbours( std::vector< char > &, size_t ) const;

	int x, y;
	size_t tentativeScore;
};


#endif //INC_24_STATE_H
