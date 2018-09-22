
#ifndef INC_10_IMICROCHIPHANDLER_H
#define INC_10_IMICROCHIPHANDLER_H

#include <cstddef>

class IMicrochipHandler {
public:
    virtual void addMicrochip(size_t) = 0;
};

#endif //INC_10_IMICROCHIPHANDLER_H
