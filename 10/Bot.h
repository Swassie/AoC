
#ifndef INC_10_BOT_H
#define INC_10_BOT_H

#include <vector>
#include <cstddef>
#include "IMicrochipHandler.h"

class Bot : public IMicrochipHandler {
public:
    Bot( size_t );
    void addMicrochip(size_t) override;
    void assignLow(IMicrochipHandler *mcHandler);
    void assignHigh(IMicrochipHandler *mcHandler);
    void lookFor( size_t, size_t );
    bool update();

private:
    size_t myNr;
    IMicrochipHandler *low, *high;
    std::vector< size_t > microchips;
    std::vector< size_t > lookForThese;
};


#endif //INC_10_BOT_H
