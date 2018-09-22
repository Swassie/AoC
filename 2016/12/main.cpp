#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	std::map< char, int > registers{ { 'a', 0 }, { 'b', 0 }, { 'c', 1 }, { 'd', 0 } };
	std::vector< std::string > instructions;
	size_t curInstruction{ 0 };

	while( std::getline( fileStream, tempString )) {
		instructions.push_back( tempString );
	}

	while( curInstruction < instructions.size() ) {
		std::istringstream instrStream{ instructions[ curInstruction ] };

		instrStream >> tempString;

		if( tempString == "cpy" ) {
			std::string src;
			char dst;

			instrStream >> src;
			instrStream >> dst;

			if( std::isdigit( src.front() )) {
				registers[ dst ] = std::stoi( src );
			}
			else {
				registers[ dst ] = registers[ src.front() ];
			}
		}
		else if( tempString == "inc" ) {
			char reg;

			instrStream >> reg;
			registers[ reg ]++;
		}
		else if( tempString == "dec" ) {
			char reg;

			instrStream >> reg;
			registers[ reg ]--;
		}
		else if( tempString == "jnz" ) {
			std::string condString;
			int cond, offset;

			instrStream >> condString;
			instrStream >> offset;

			cond = std::isdigit( condString.front() ) ? std::stoi( condString ) : registers[ condString.front() ];

			if( cond ) {
				curInstruction += offset;
				continue;
			}
		}

		++curInstruction;
	}

	std::cout << "Register a: " << registers[ 'a' ];
	return 0;
}