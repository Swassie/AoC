#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>

//enum class Direction { North, East, South, West };

int main() {

    std::cout << "Enter puzzle input: ";

    //Direction direction{ Direction::North };
    std::array< int, 2 > coords{ 0, 0 };
    char turnDirection;
    std::vector< std::array< int, 2 > > visitedCoords{ { 0, 0 } };
    size_t steps, direction{ 0 }; // Direction: 0: N, 1: E, 2: S, 3: W.
    std::string inputString, instruction;

    std::getline( std::cin, inputString );
    std::istringstream inputStream( inputString );

    while( inputStream >> instruction ) {
        turnDirection = instruction[0];
        steps = static_cast< size_t > ( std::stoi( instruction.substr( 1, std::string::npos ) ) );
        //std::cout << instruction << "  " << turnDirection << "  " << steps << std::endl;
        if( turnDirection == 'L' ) {
            --direction;
            if( direction == -1 ) {
                direction = 3;
            }
        }
        else {
            direction = ++direction % 4;
        }

        for( int i = 0; i < steps; ++i ) {
            switch (direction) {
                case 0:
                    ++coords[0];
                    break;
                case 1:
                    ++coords[1];
                    break;
                case 2:
                    --coords[0];
                    break;
                case 3:
                    --coords[1];
                    break;
                default:
                    return -1;
            }
            std::vector< std::array< int, 2 > >::iterator it;
            it = find( visitedCoords.begin(), visitedCoords.end(), coords );
            if( it == visitedCoords.end() ) {
                visitedCoords.push_back( coords );
            }
            else {
                std::cout << "Distance: " << std::abs( coords[ 0 ] ) + std::abs( coords[ 1 ] );
                return 0;
            }
        }
    }
    std::cout << "Distance: " << std::abs( coords[ 0 ] ) + std::abs( coords[ 1 ] );
    return 0;
}