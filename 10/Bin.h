
#ifndef INC_10_BIN_H
#define INC_10_BIN_H


#include <vector>
#include "IMicrochipHandler.h"

class Bin : public IMicrochipHandler {
public:
    void addMicrochip(size_t) override;
    std::vector< size_t >& getMicrochips();

private:
    std::vector< size_t > microchips;
};

#endif //INC_10_BIN_H
