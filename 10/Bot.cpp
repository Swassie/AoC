
#include <algorithm>
#include <iostream>
#include "Bot.h"

Bot::Bot( size_t botNr )
        : myNr{ botNr }, low{ nullptr }, high{ nullptr } {}

void Bot::addMicrochip(size_t chip) {
    microchips.push_back( chip );
    std::sort( microchips.begin(), microchips.end() );
}

void Bot::assignLow(IMicrochipHandler *mcHandler) {
    low = mcHandler;
}

void Bot::assignHigh(IMicrochipHandler *mcHandler) {
    high = mcHandler;
}

bool Bot::update() {
    bool changed{ false };

    if( microchips.size() == 2 ) {
        if( lookForThese == microchips ) {
            std::cout << "Bot #" << myNr << " is comparing " <<
                      lookForThese[ 0 ] << " and " << lookForThese[ 1 ] << std::endl;
        }
        if( high ) {
            high->addMicrochip(microchips[1]);
            microchips.erase( microchips.begin() + 1 );
            changed = true;
        }
        if( low ) {
            low->addMicrochip(microchips[0]);
            microchips.erase( microchips.begin() );
            changed = true;
        }
    }
    return changed;
}

void Bot::lookFor( size_t chip1, size_t chip2 ) {
    lookForThese.push_back( chip1 );
    lookForThese.push_back( chip2 );
    std::sort( lookForThese.begin(), lookForThese.end() );
}
