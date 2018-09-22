#include <iostream>
#include <fstream>

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string numbers;
	int sum{ 0 };

	std::getline( fileStream, numbers );

	for( int i{ 0 }; i < numbers.length() - 1; ++i ) {
		if( numbers[ i ] == numbers[ i + 1 ] ) {
			sum += numbers[ i ] - '0';
		}
	}

	if( numbers.front() == numbers.back() ) {
		sum += numbers.front() - '0';
	}

	std::cout << "Sum: " << sum << std::endl;

	sum = 0;
	unsigned long offset{ numbers.length() / 2 };

	for( int i{ 0 }; i < numbers.length(); ++i ) {
		if( numbers[ i ] == numbers[( i + offset ) % numbers.length()]) {
			sum += numbers[ i ] - '0';
		}
	}

	std::cout << "Sum: " << sum << std::endl;

	return 0;
}