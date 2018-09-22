#include <iostream>
#include <algorithm>

std::string doChecksum( std::string str ) {
	std::string checksum;
	for( int i{ 0 }; i < str.size(); i += 2 ) {
		checksum.push_back( str[ i ] == str[ i + 1 ] ? '1' : '0' );
	}
	return checksum;
}

int main() {

	const std::string input{ "11101000110010100" };
	const size_t diskSize{ 35651584 };
	std::string a{ input }, b, checksum;

	while( a.size() < diskSize ) {
		b = a;
		std::reverse( b.begin(), b.end() );
		std::for_each( b.begin(), b.end(), [] ( char &c ) {
			c = c == '0' ? '1' : '0';
		});
		a = a + "0" + b;
	}

	a = a.substr( 0, diskSize );
	checksum = doChecksum( a );

	while( checksum.size() % 2 == 0 ) {
		checksum = doChecksum( checksum );
	}

	std::cout << "Checksum: " << checksum;

	return 0;
}