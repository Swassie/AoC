
#ifndef INC_15_DISC_H
#define INC_15_DISC_H


#include <glob.h>

class Disc {
public:
	Disc( size_t discNr, size_t positionCount, size_t startPosition );
	size_t tick( size_t steps );
	bool correctAligned() const;

	size_t discNr, positionCount, position;
};


#endif //INC_15_DISC_H
