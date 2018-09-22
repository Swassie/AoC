
#include "Node.h"

bool operator==( const Node &a, const Node &b ) {
	return a.x == b.x && a.y == b.y && a.size == b.size && a.used == b.used;
}