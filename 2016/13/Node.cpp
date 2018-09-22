#include "Node.h"

std::vector< Node > Node::findOpenNeighbours() {
	std::vector< Node > ret;

	if( x != 0 ) {
		ret.push_back({ x - 1, y });
	}
	if( y != 0 ) {
		ret.push_back({ x, y - 1 });
	}
	ret.push_back({ x, y + 1 });
	ret.push_back({ x + 1, y });

	ret.erase( std::remove_if( ret.begin(), ret.end(), [] ( Node &node ) {
		const size_t puzzleInput{ 1362 };
		size_t &x{ node.x }, &y{ node.y };

		size_t sum{ x*x + 3*x + 2*x*y + y + y*y };
		sum += puzzleInput;

		return std::bitset< 64 >( sum ).count() % 2 == 1;
	}), ret.end());

	return ret;
}


std::pair< size_t, size_t > Node::getCoords() const {
	return { x, y };
}
