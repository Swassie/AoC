#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

int main() {

#if 0
    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    size_t TLSCount{ 0 };

    while( std::getline( fileStream, tempString )) {
        std::istringstream ipStream{ tempString };
        bool validABBA{ false }, insideHypernet{ false };
        std::deque< char > q;
        char c;

        while( ipStream >> c ) {
            if( c == '[' ) {
                insideHypernet = true;
                q.clear();
            }
            else if( c == ']' ) {
                insideHypernet = false;
                q.clear();
            }

            q.push_back( c );
            if( q.size() == 4 ) {
                if( q[ 0 ] == q[ 3 ] && q[ 1 ] == q[ 2 ] && q[ 0 ] != q[ 1 ] ) {
                    if( insideHypernet ) {
                        validABBA = false;
                        break;
                    }
                    else {
                        validABBA = true;
                    }
                }
                q.pop_front();
            }
        }
        if( validABBA ) {
            ++TLSCount;
        }
    }
    std::cout << TLSCount;
#else
    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    size_t SSLCount{ 0 };

    while( std::getline( fileStream, tempString )) {
        std::istringstream ipStream{ tempString };
        bool insideHypernet{ false };
        std::deque< char > q;
        std::vector< std::deque< char > > supernet, hypernet;
        char c;

        while( ipStream >> c ) {
            if( c == '[' ) {
                insideHypernet = true;
                q.clear();
            }
            else if( c == ']' ) {
                insideHypernet = false;
                q.clear();
            }

            q.push_back( c );
            if( q.size() == 3 ) {
                if( q[ 0 ] == q[ 2 ] && q[ 0 ] != q[ 1 ] ) {
                    if( insideHypernet ) {
                        hypernet.push_back( q );
                        auto it = std::find_if( supernet.begin(), supernet.end(), [ q ] ( std::deque< char > &q2 ) {
                            return q[ 0 ] == q2[ 1 ] && q[ 1 ] == q2[ 0 ];
                        });
                        if( it != supernet.end() ) {
                            ++SSLCount;
                            break;
                        }
                    }
                    else {
                        supernet.push_back( q );
                        auto it = std::find_if( hypernet.begin(), hypernet.end(), [ q ] ( std::deque< char > &q2 ) {
                            return q[ 0 ] == q2[ 1 ] && q[ 1 ] == q2[ 0 ];
                        });
                        if( it != hypernet.end() ) {
                            ++SSLCount;
                            break;
                        }
                    }
                }
                q.pop_front();
            }
        }
    }
    std::cout << SSLCount;
#endif
    return 0;
}