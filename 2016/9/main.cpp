#include <iostream>
#include <fstream>
#include <sstream>

size_t decompress( std::string &str, size_t reps ) {
    std::istringstream compressed{ str };
    size_t decompressedLength{ 0 };
    char c;

    while( compressed >> c ) {
        if( c == '(' ) {
            size_t length{ 0 }, innerReps{ 0 };
            compressed >> length;
            compressed.ignore();
            compressed >> innerReps;
            compressed.ignore();
            char *buf{ new char[ length ]};
            compressed.read( buf, length );
            std::string tempString{ std::string( buf, length ) };

            decompressedLength += decompress( tempString, innerReps );
            continue;
        }
        ++decompressedLength;
    }
    return decompressedLength * reps;
}

int main() {

#if 0
    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    std::ostringstream decompressed;
    size_t decompressedLength{ 0 };

    while( std::getline( fileStream, tempString )) {
        std::istringstream compressed{ tempString };
        char c;

        while( compressed >> c ) {
            if( c == '(' ) {
                size_t length{ 0 }, reps{ 0 };
                compressed >> length;
                compressed.ignore();
                compressed >> reps;
                compressed.ignore();
                char *buf{ new char[ length ]};
                compressed.read( buf, length );
                tempString = std::string( buf, length );
                std::string repeatedString;

                for( int i = 0; i < reps; ++i ) {
                    repeatedString += tempString;
                }
                decompressed << repeatedString;
                continue;
            }
            decompressed << c;
        }
        decompressed.seekp( 0, std::ios::end );
        decompressedLength += decompressed.tellp();
    }
#else
    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    size_t decompressedLength{ 0 };

    while( std::getline( fileStream, tempString )) {

        decompressedLength += decompress( tempString, 1 );
    }
#endif
    std::cout << decompressedLength;
    return 0;
}