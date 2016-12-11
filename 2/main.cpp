#include <iostream>
#include <fstream>
#include <sstream>

int main() {
#if 0
    int row{ 2 }, col{ 2 };
    char keyPad[ 5 ][ 5 ]{ {'-','-','-','-','-'},
                            {'-','1','2','3','-'},
                            {'-','4','5','6','-'},
                            {'-','7','8','9','-'},
                            {'-','-','-','-','-'} };
#else
    int row{ 3 }, col{ 1 };
    char keyPad[ 7 ][ 7 ]{ {'-','-','-','-','-','-','-'},
                            {'-','-','-','1','-','-','-'},
                            {'-','-','2','3','4','-','-'},
                            {'-','5','6','7','8','9','-'},
                            {'-','-','A','B','C','-','-'},
                            {'-','-','-','D','-','-','-'},
                            {'-','-','-','-','-','-','-'} };
#endif

    std::string tempLine;
    std::ifstream fileStream{ "../input.txt" };
    if( !fileStream.is_open() ) {
        std::cerr << "Could not open file.";
        return -1;
    }

    while( std::getline( fileStream, tempLine ) ) {
        std::istringstream inputLine{ tempLine };
        char direction;
        while( inputLine >> direction ) {
            int oldRow{ row }, oldCol{ col };
            switch( direction ) {
                case 'U':
                    --row;
                    break;
                case 'D':
                    ++row;
                    break;
                case 'L':
                    --col;
                    break;
                case 'R':
                    ++col;
                    break;
                default:
                    return -1;
            }

            if( keyPad[ row ][ col ] == '-' ) {
                row = oldRow;
                col = oldCol;
            }
        }
        std::cout << keyPad[ row ][ col ];
    }
    return 0;
}