
#include "Display.h"
#include <iostream>

Display::Display(size_t rows, size_t cols) : pixels( rows, std::vector< uint8_t >( cols, 0 )), mRows( rows ), mCols( cols ) {

}

void Display::rect( size_t width, size_t height ) {
    for( int row = 0; row < height; ++row ) {
        for( int col = 0; col < width; ++col ) {
            pixels[ row ][ col ] = 1;
        }
    }
}

void Display::rotateRow( size_t row, size_t steps ) {
    for( int i = 0; i < steps; ++i ) {
        uint8_t last{ pixels[ row ].back() };
        pixels[ row ].pop_back();
        pixels[ row ].insert( pixels[ row ].begin(), last );
    }
}

void Display::rotateCol( size_t col, size_t steps ) {
    for( int i = 0; i < steps; ++i ) {
        uint8_t last{ pixels[ mRows - 1 ][ col ]};

        for( size_t row = mRows - 1; row > 0; --row ) {
            pixels[ row  ][ col ] = pixels[ row - 1 ][ col ];
        }

        pixels[ 0 ][ col ] = last;
    }
}

void Display::print() const{
    for( int row = 0; row < mRows; ++row ) {
        for( int col = 0; col < mCols; ++col ) {
            std::cout << (( pixels[ row ][ col ] == 0 ) ? ' ' : '#' );
        }
        std::cout << std::endl;
    }
}

size_t Display::nrLitPixels() const {
    size_t nrLitPixels{ 0 };
    for( int row = 0; row < mRows; ++row ) {
        for( int col = 0; col < mCols; ++col ) {
            nrLitPixels += pixels[ row ][ col ];
        }
    }
    return nrLitPixels;
}
