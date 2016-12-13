
#include "Bin.h"

void Bin::addMicrochip(size_t chip) {
    microchips.push_back( chip );
}

std::vector<size_t>& Bin::getMicrochips() {
    return microchips;
}
