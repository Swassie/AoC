#include <algorithm>
#include <iostream>
#include <vector>

int main() {

	const size_t rowCount{ 400000 };
	std::string input{ ".^..^....^....^^.^^.^.^^.^.....^.^..^...^^^^^^.^^^^.^.^^^^^^^.^^^^^..^.^^^.^^..^.^^.^....^.^...^^.^." };
	std::vector< std::string > rows{ input };

	while( rows.size() < rowCount ) {
		std::string row{ "." + rows.back() + "." };
		std::string newRow;

		for( size_t i{ 1 }; i < ( row.size() - 1 ); ++i ) {
			std::string section{ row.substr( i - 1, 3 ) };
			if( section == "^^."  || section == ".^^" || section == "^.." || section == "..^" ) {
				newRow += '^';
			}
			else {
				newRow += '.';
			}
		}
		rows.push_back( newRow );
	}

	size_t safeCount{ 0 };
	for( std::string &row : rows ) {
		safeCount += std::count( row.begin(), row.end(), '.' );
	}

	std::cout << "# of safe tiles: " << safeCount;

	return 0;
}