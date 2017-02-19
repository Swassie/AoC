
#ifndef INC_24_STATE_H
#define INC_24_STATE_H


#include <vector>
#include <cstdint>
#include <cstddef>

class State {
public:
	size_t estimateCost() const;
	std::vector< State > getNeighbours( std::vector< char > &, size_t ) const;

	int x, y;
	size_t gScore, fScore;
	uint32_t numbers;
	//std::vector< uint8_t > numbers;
};


#endif //INC_24_STATE_H
