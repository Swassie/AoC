#include <iostream>
#include <sstream>
#include <bitset>
#include <set>
#include <utility>
#include <vector>
#include "../10/KnotHash.h"

int main()
{
	const std::string input{ "ljoxqyyw" };
	int usedSquares{ 0 };
	int regions{ 0 };
	std::vector< std::string > grid;

	for( int row{ 0 }; row < 128; ++row )
	{
		std::string tempString{ input + "-" };
		tempString.append( std::to_string( row ));

		std::string hash{ KnotHash::hash( tempString, 64 )};
		grid.push_back( "" );

		for( const char& hex: hash )
		{
			unsigned dec;
			std::stringstream ss;
			ss << std::hex << hex;
			ss >> dec;
			std::bitset< 4 > bits{ dec };
			usedSquares += bits.count();

			grid[ row ] += bits.to_string();
		}
	}

	std::cout << "Used squares: " << usedSquares << std::endl;

	for( size_t row{ 0 }; row < grid.size(); ++row )
	{
		for( size_t col{ 0 }; col < grid[ row ].size(); ++col )
		{
			if( grid[ row ][ col ] == '0' )
			{
				continue;
			}

			++regions;

			using Coord = std::pair< int, int >;
			std::set< Coord > openSet;
			Coord current;

			openSet.emplace( col, row );

			while( !openSet.empty() )
			{
				current = *openSet.begin();
				openSet.erase( current );
				grid[ current.second ][ current.first ] = '0';

				for( int i{ -1 }; i < 2; i += 2 )
				{
					if( current.second + i >= 0 &&
					    current.second + i < grid.size() &&
					    grid[ current.second + i ][ current.first ] == '1' )
					{
						openSet.emplace( current.first, current.second + i );
					}

					if( current.first + i >= 0 &&
					    current.first + i < grid[ current.second ].size() &&
					    grid[ current.second ][ current.first + i ] == '1' )
					{
						openSet.emplace( current.first + i, current.second );
					}
				}
			}
		}
	}

	std::cout << "Number of regions: " << regions << std::endl;

	return 0;
}
