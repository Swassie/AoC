#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Layer {
	int depth;
	int range;
};

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::vector< Layer > firewall;
	std::string tempString;

	while( std::getline( fileStream, tempString )) {
		std::istringstream rowStream{ tempString };

		int depth, range;
		rowStream >> depth;
		rowStream.ignore( 2 );
		rowStream >> range;

		firewall.push_back({ depth, range });
	}

	int severity{ 0 };

	for( const Layer& layer: firewall ) {
		int period{( layer.range - 1 ) * 2 };
		if( layer.depth % period == 0 ) {
			severity += layer.depth * layer.range;
		}
	}

	std::cout << "Severity: " << severity << std::endl;

	int delay{ 0 };
	bool detected{ false };

	do {
		detected = false;

		for( const Layer& layer: firewall ) {
			int period{( layer.range - 1 ) * 2 };
			if(( delay + layer.depth ) % period == 0 ) {
				detected = true;
				break;
			}
		}
		++delay;
	} while( detected );

	--delay;

	std::cout << "Smallest delay: " << delay << std::endl;

	return 0;
}