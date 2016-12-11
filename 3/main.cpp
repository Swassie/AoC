#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    size_t side1, side2, side3, count{ 0 };

    while( 1 ) {
        std::getline( fileStream, tempString );
        std::istringstream inputLine1{ tempString };
        std::getline( fileStream, tempString );
        std::istringstream inputLine2{ tempString };
        std::getline( fileStream, tempString );
        std::istringstream inputLine3{ tempString };
        if( ! fileStream.good() ) {
            break;
        }
        for( int i = 0; i < 3; ++i ) {
            inputLine1 >> side1;
            inputLine2 >> side2;
            inputLine3 >> side3;

            if ((side1 + side2 > side3) &&
                (side2 + side3 > side1) &&
                (side3 + side1 > side2)) {
                ++count;
            }
        }
    }
    std::cout << count;
    return 0;
}