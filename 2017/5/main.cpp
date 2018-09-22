#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::vector< int > instructions;
	int instruction;

	while( fileStream >> instruction ) {
		instructions.push_back( instruction );
	}

	int PC{ 0 };
	int steps{ 0 };

	while( PC < instructions.size() ) {

		if( false ) { // Part 1
			PC += instructions[ PC ]++;
		}
		else { // Part 2
			instruction = instructions[ PC ];
			instructions[ PC ] += instruction >= 3 ? -1 : 1;
			PC += instruction;
		}
		++steps;
	}

	std::cout << "Steps: " << steps << std::endl;

	return 0;
}