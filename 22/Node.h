
#ifndef INC_22_NODE_H
#define INC_22_NODE_H

#include <cstddef>

class Node {
public:
	int x, y;
	size_t size, used, avail;
};

bool operator==( const Node &a, const Node &b );

#endif //INC_22_NODE_H
