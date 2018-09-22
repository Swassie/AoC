#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

class Tower {
public:
	Tower() : name( "" ), weight( 0 ), totalWeight( 0 ) {}
	Tower( std::string& name, int weight ) : name( name ), weight( weight ), totalWeight( weight ) {}

	bool haveChild( const std::string& name ) const {
		for( const Tower& tower: subTowers ) {
			if( tower.name == name ) {
				return true;
			}
		}
		return false;
	}

	int calculateTotalWeight() {
		totalWeight = weight;

		for( Tower& child: subTowers ) {
			totalWeight += child.calculateTotalWeight();
		}

		return totalWeight;
	}

	int findImbalance() {
		if( subTowers.empty() ) {
			return -1;
		}

		for( Tower& child: subTowers ) {
			int res{ child.findImbalance()};
			if( res != -1 ) {
				return res;
			}
		}

		std::sort( subTowers.begin(), subTowers.end(), [] ( const Tower& a, const Tower& b ) {
			return a.totalWeight < b.totalWeight;
		});

		if( subTowers[ 0 ].totalWeight != subTowers.back().totalWeight ) {
			if( subTowers[ 0 ].totalWeight != subTowers[ 1 ].totalWeight ) {
				return subTowers[ 0 ].weight + subTowers[ 1 ].totalWeight - subTowers[ 0 ].totalWeight;
			}
			else if( subTowers.back().totalWeight != subTowers[ 1 ].totalWeight ) {
				return subTowers.back().weight + subTowers[ 1 ].totalWeight - subTowers.back().totalWeight;
			}
		}
		return -1;
	}

	std::string name;
	int weight, totalWeight;
	std::vector< Tower > subTowers;
};

int buildTree( Tower& t, const std::vector< Tower >& towers ) {
	for( Tower& child: t.subTowers ) {
		for( const Tower& tower: towers ) {
			if( child.name == tower.name ) {
				child = tower;
				buildTree( child, towers );
				break;
			}
		}
	}
}

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::vector< Tower > towers;
	std::string tempString;
	int weight;

	while( std::getline( fileStream, tempString )) {
		tempString.erase( std::remove( tempString.begin(), tempString.end(), ',' ), tempString.end());

		std::istringstream rowStream{ tempString };

		rowStream >> tempString;
		rowStream.ignore( 2 );
		rowStream >> weight;
		rowStream.ignore( 5 );

		Tower tower( tempString, weight );

		while( rowStream >> tempString ) {
			tower.subTowers.emplace_back( tempString, 0 );
		}

		towers.push_back( tower );
	}

	Tower bottom;

	for( const Tower& tower1: towers ) {
		bool isBottom{ true };
		for( const Tower& tower2: towers ) {
			if( tower2.haveChild( tower1.name )) {
				isBottom = false;
				break;
			}
		}
		if( isBottom ) {
			bottom = tower1;
			break;
		}
	}

	std::cout << "Bottom program: " << bottom.name << std::endl;

	buildTree( bottom, towers );
	bottom.calculateTotalWeight();

	std::cout << "Weight should be: " << bottom.findImbalance() << std::endl;

	return 0;
}