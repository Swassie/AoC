#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main() {
	std::ifstream fileStream{ "../input.txt" };
	std::vector< std::string > passphrase1;
	std::vector< std::string > passphrase2;
	std::string tempString;
	int validCount1{ 0 };
	int validCount2{ 0 };

	while( std::getline( fileStream, tempString )) {
		std::istringstream rowStream{ tempString };

		passphrase1.clear();
		passphrase2.clear();
		bool valid1{ true };
		bool valid2{ true };

		while( rowStream >> tempString ) {
			auto iter( std::find( passphrase1.begin(), passphrase1.end(), tempString ) );

			if( iter != passphrase1.end() ) {
				valid1 = false;
			}

			passphrase1.push_back( tempString );

			std::sort( tempString.begin(), tempString.end() );

			iter = std::find( passphrase2.begin(), passphrase2.end(), tempString );

			if( iter != passphrase2.end() ) {
				valid2 = false;
			}

			passphrase2.push_back( tempString );
		}

		if( valid1 ) {
			++validCount1;
		}

		if( valid2 ) {
			++validCount2;
		}
	}

	std::cout << "Count: " << validCount1 << std::endl;
	std::cout << "Count: " << validCount2 << std::endl;

	return 0;
}