
#ifndef INC_8_DISPLAY_H
#define INC_8_DISPLAY_H

#include <cstdint>
#include <cstddef>
#include <vector>

class Display {
public:
    Display( size_t, size_t );

    void rect( size_t, size_t );
    void rotateRow( size_t, size_t );
    void rotateCol( size_t, size_t );
    size_t nrLitPixels() const;
    void print() const;

private:
    std::vector< std::vector< uint8_t > > pixels;
    size_t mRows, mCols;
};


#endif //INC_8_DISPLAY_H
