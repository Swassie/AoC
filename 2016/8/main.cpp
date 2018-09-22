#include <iostream>
#include <fstream>
#include <sstream>
#include "Display.h"

int main() {

    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;

    Display display{ 6, 50 };

    while( std::getline( fileStream, tempString )) {
        std::istringstream operationStream{ tempString };
        operationStream >> tempString;

        if( tempString == "rect" ) {
            size_t width, height;
            operationStream >> width;
            operationStream.ignore();
            operationStream >> height;
            display.rect( width, height );
        }
        else if( tempString == "rotate" ) {
            operationStream >> tempString;

            if( tempString == "row" ) {
                operationStream.ignore( 3 );
                size_t row, steps;
                operationStream >> row;
                operationStream.ignore( 4 );
                operationStream >> steps;
                display.rotateRow( row, steps );
            }
            else if( tempString == "column" ) {
                operationStream.ignore( 3 );
                size_t col, steps;
                operationStream >> col;
                operationStream.ignore( 4 );
                operationStream >> steps;
                display.rotateCol( col, steps );
            }
        }
    }
    std::cout << display.nrLitPixels() << std::endl << std::endl;
    display.print();
    return 0;
}