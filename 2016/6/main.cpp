#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <array>
#include <algorithm>

int main() {

    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    using charCount = std::pair< char, size_t >;

    // Init the vector
    std::getline( fileStream, tempString );
    std::vector< std::vector< charCount > > countVector{ tempString.size() };
    fileStream.seekg( 0 );

    while( std::getline( fileStream, tempString )) {
        std::istringstream message{ tempString };
        char c{ 0 };
        size_t i{ 0 };

        while( message >> c ) {
            std::vector< charCount >::iterator it;
            it = std::find_if( countVector[ i ].begin(), countVector[ i ].end(), [ c ] ( charCount &p ) {
                return p.first == c;
            });
            if( it != countVector[ i ].end() ) {
                it->second++;
            }
            else {
                countVector[ i ].push_back( { c, 1 } );
            }
            ++i;
        }
    }

    for( size_t i = 0; i < countVector.size(); ++i ) {
        std::sort( countVector[ i ].begin(), countVector[ i ].end(), [] ( const charCount &p1, const charCount &p2) {
            return p1.second > p2.second;
        });
        std::cout << countVector[ i ].back().first;
    }

    return 0;
}