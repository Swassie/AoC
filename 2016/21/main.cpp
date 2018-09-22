#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void swapPosition( std::string &str, size_t x, size_t y ) {
	char temp{ str[ x ] };
	str[ x ] = str[ y ];
	str[ y ] = temp;
}

void swapLetter( std::string &str, char x, char y ) {
	for( char &c : str ) {
		if( c == x ) {
			c = y;
		}
		else if( c == y ) {
			c = x;
		}
	}
}

void rotateLeft( std::string &str, size_t steps ) {
	for( int i{ 0 }; i < steps; ++i ) {
		std::rotate( str.begin(), str.begin() + 1, str.end() );
	}
}

void rotateRight( std::string &str, size_t steps ) {
	for( int i{ 0 }; i < steps; ++i ) {
		std::rotate( str.rbegin(), str.rbegin() + 1, str.rend() );
	}
}

void rotateLetter( std::string &str, char c ) {
	size_t steps{ str.find_first_of( c ) };

	steps = steps >= 4 ? steps + 2 : steps + 1;
	rotateRight( str, steps );
}

void reverse( std::string &str, size_t x, size_t y ) {
	std::reverse( str.begin() + x, str.begin() + y + 1 );
}

void move( std::string &str, size_t x, size_t y ) {
	char c{ str[ x ] };
	str.erase( str.begin() + x );
	str.insert( str.begin() + y, c );
}


int main() {

	std::string password{ "abcdefgh" }, tempString;
	std::ifstream fileStream{ "../input.txt" };
	std::vector< std::string > operations;

	std::cout << "Original password: " << password << std::endl;

	while( std::getline( fileStream, tempString )) {
		operations.push_back( tempString );
	}

	for( std::string str : operations ) {
		std::istringstream ss{ str };
		ss >> tempString;

		if( tempString == "swap" ) {
			ss >> tempString;

			if( tempString == "position" ) {
				size_t x, y;
				ss >> x >> tempString >> tempString >> y;
				swapPosition( password, x, y );
			}
			else if( tempString == "letter" ) {
				char x, y;
				ss >> x >> tempString >> tempString >> y;
				swapLetter( password, x, y );
			}
		}
		else if( tempString == "rotate" ) {
			ss >> tempString;

			if( tempString == "based" ) {
				char c;
				ss.ignore( 23 );
				ss >> c;
				rotateLetter( password, c );
			}
			else if( tempString == "left" ) {
				size_t steps;
				ss >> steps;
				rotateLeft( password, steps );
			}
			else if( tempString == "right" ) {
				size_t steps;
				ss >> steps;
				rotateRight( password, steps );
			}
		}
		else if( tempString == "reverse" ) {
			size_t x, y;
			ss >> tempString >> x >> tempString >> y;
			reverse( password, x, y );
		}
		else if( tempString == "move" ) {
			size_t x, y;
			ss >> tempString >> x >> tempString >> tempString >> y;
			move( password, x, y );
		}
	}

	std::cout << "Scrambled password: " << password << std::endl;
	password = "fbgdceah";

	for( auto it = operations.rbegin(); it != operations.rend(); ++it ) {
		std::istringstream ss{ *it };
		ss >> tempString;

		if( tempString == "swap" ) {
			ss >> tempString;

			if( tempString == "position" ) {
				size_t x, y;
				ss >> x >> tempString >> tempString >> y;
				swapPosition( password, x, y );
			}
			else if( tempString == "letter" ) {
				char x, y;
				ss >> x >> tempString >> tempString >> y;
				swapLetter( password, x, y );
			}
		}
		else if( tempString == "rotate" ) {
			ss >> tempString;

			if( tempString == "based" ) {
				char c;
				ss.ignore( 23 );
				ss >> c;
				size_t index{ password.find_first_of( c ) };
				for( size_t i{ 0 }; i < password.size(); ++i ) {
					if( ( i + i + 1 + ( i >= 4 ? 1 : 0 ) ) % password.size() == index ) {
						rotateLeft( password, ( i + 1 + ( i >= 4 ? 1 : 0 ) ) );
						break;
					}
				}
			}
			else if( tempString == "left" ) {
				size_t steps;
				ss >> steps;
				rotateRight( password, steps );
			}
			else if( tempString == "right" ) {
				size_t steps;
				ss >> steps;
				rotateLeft( password, steps );
			}
		}
		else if( tempString == "reverse" ) {
			size_t x, y;
			ss >> tempString >> x >> tempString >> y;
			reverse( password, x, y );
		}
		else if( tempString == "move" ) {
			size_t x, y;
			ss >> tempString >> x >> tempString >> tempString >> y;
			move( password, y, x );
		}
	}

	std::cout << "Unscrambled password: " << password << std::endl;

	return 0;
}