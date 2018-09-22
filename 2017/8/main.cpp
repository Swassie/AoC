#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <limits>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	std::map< std::string, int > regMap;
	std::string dstReg, op, condReg, condOp;
	int value, condValue;
	int maxReg{ 0 };

	while( std::getline( fileStream, tempString )) {
		std::istringstream rowStream{ tempString };

		rowStream >> dstReg;
		rowStream >> op;
		rowStream >> value;
		rowStream.ignore( 4 );
		rowStream >> condReg;
		rowStream >> condOp;
		rowStream >> condValue;

		if( op == "dec" ) {
			value = -value;
		}

		if( condOp == ">" && regMap[ condReg ] > condValue ||
				condOp == "<" && regMap[ condReg ] < condValue ||
				condOp == ">=" && regMap[ condReg ] >= condValue ||
				condOp == "<=" && regMap[ condReg ] <= condValue ||
				condOp == "==" && regMap[ condReg ] == condValue ||
				condOp == "!=" && regMap[ condReg ] != condValue ) {
			regMap[ dstReg ] += value;
			maxReg = regMap[ dstReg ] > maxReg ? regMap[ dstReg ] : maxReg;
		}
	}

	std::cout << "Max value during execution: " << maxReg << std::endl;

	maxReg = std::numeric_limits< int >::min();

	for( const auto& pair: regMap ) {
		maxReg = pair.second > maxReg ? pair.second : maxReg;
	}

	std::cout << "Max value after execution: " << maxReg << std::endl;

	return 0;
}