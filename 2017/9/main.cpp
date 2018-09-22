#include <iostream>
#include <sstream>
#include <fstream>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	int totalScore{ 0 }, groupScore{ 0 }, garbageChars{ 0 };
	bool garbage{ false };
	char c;

	std::getline( fileStream, tempString );

	std::istringstream input{ tempString };

	while( input >> c ) {
		if( garbage ) {
			switch( c ) {
				case '!':
					input.ignore();
					break;
				case '>':
					garbage = false;
					break;
				default:
					++garbageChars;
					break;
			}
		}
		else {
			switch( c ) {
				case '{':
					++groupScore;
					totalScore += groupScore;
					break;
				case '}':
					--groupScore;
					break;
				case '<':
					garbage = true;
					break;
				default:
					break;
			}
		}
	}

	std::cout << "Total score: " << totalScore << std::endl;
	std::cout << "Garbage characters: " << garbageChars << std::endl;

	return 0;
}