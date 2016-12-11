#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

int main() {

    std::ifstream fileStream{ "../input.txt" };
    std::string tempLine{};
    using charCount = std::pair< char, size_t >;
    size_t sectorSum{ 0 };

    while( std::getline( fileStream, tempLine ) ) {
        std::istringstream encryptedLine{ tempLine };
        std::stringstream roomName;
        std::vector< charCount > charVector{};
        char c{ 0 };

        // Read room name
        while( true  ) {
            int peek{ encryptedLine.peek() };
            if( peek >= 48 && peek <= 57 ) {
                break;
            }
            encryptedLine >> c;
            roomName << c;
            if( c == '-' ) {
                continue;
            }
            std::vector< charCount >::iterator it;
            it = std::find_if( charVector.begin(), charVector.end(), [ c ] ( charCount &p ) {
                if( p.first == c ) {
                    p.second++;
                    return true;
                }
                return false;
            } );
            if( it == charVector.end() ) {
                charVector.push_back( { c, 1 } );
            }
        }
        // Sort charVector in alphabetical order
        std::sort( charVector.begin(), charVector.end(), [] ( const charCount &p1, const charCount &p2 ) {
            return p1.first <= p2.first;
        } );
        // Sort them in count order with stable_sort
        std::stable_sort( charVector.begin(), charVector.end(), [] ( const charCount &p1, const charCount &p2 ) {
            return p1.second > p2.second;
        } );

        // Read sector ID
        size_t sectorID;
        encryptedLine >> sectorID;
        encryptedLine.ignore( 1 );

        // Verify checksum
        bool OK{ true };
        for( int i = 0; i < 5; ++i ) {
            encryptedLine >> c;
            if( c != charVector[ i ].first ) {
                OK = false;
            }
        }

        if( !OK ) {
            continue;
        }
        sectorSum += sectorID;

        // Decrypt room name
        roomName.seekp( 0 );
        roomName.seekg( 0 );
        while( roomName >> c ) {
            if(c == '-') {
                roomName << " ";
            }
            else {
                c = static_cast< char >(((c - 97 + sectorID) % 26) + 97 );
                roomName << c;
            }
        }
        std::cout << roomName.str() << " : " << sectorID << std::endl;
    }
    std::cout << sectorSum;
    return 0;
}