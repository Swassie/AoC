
#include "Disc.h"

Disc::Disc( size_t discNr, size_t positionCount, size_t startPosition )
		: discNr( discNr ), positionCount( positionCount ), position( startPosition )
{ }

size_t Disc::tick( size_t steps ) {
	position = ( position + steps ) % positionCount;
	return position;
}

bool Disc::correctAligned() const {
	return (( discNr + position ) % positionCount ) == 0;
}
