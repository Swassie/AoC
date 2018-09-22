#include <cmath>
#include <iostream>
#include <map>
#include <utility>


enum class Direction { left, right, up, down };

int main() {

	int input{ 0 };
	std::cout << "Enter input: ";
	std::cin >> input;

	int square{ 2 }, side{ 3 };

	while( square + std::floor( side / 2 ) < input ) {
		square += side - 1;

		if( square > std::pow( side, 2 )) {
			++square;
			side += 2;
		}
	}

	std::cout << "Steps: " << std::abs( square - input ) + ( side - 1 ) / 2 << std::endl;

	std::map< std::pair< int, int >, int > mem;

	mem[{ 0, 0 }] = 1;

	std::pair< int, int > pos{ 0, 0 };
	Direction dir{ Direction::right };

	while( mem[ pos ] < input ) {
		std::map< std::pair< int, int >, int >::iterator iter;

		switch( dir ) {
			case Direction::left:
				--pos.first;
				iter = mem.find({ pos.first, pos.second - 1 });
				dir = iter == mem.end() ? Direction::down : Direction::left;
				break;
			case Direction::right:
				++pos.first;
				iter = mem.find({ pos.first, pos.second + 1 });
				dir = iter == mem.end() ? Direction::up : Direction::right;
				break;
			case Direction::up:
				++pos.second;
				iter = mem.find({ pos.first - 1, pos.second });
				dir = iter == mem.end() ? Direction::left : Direction::up;
				break;
			case Direction::down:
				--pos.second;
				iter = mem.find({ pos.first + 1, pos.second });
				dir = iter == mem.end() ? Direction::right : Direction::down;
				break;
		}

		int sum{ 0 };

		iter = mem.find({ pos.first + 1, pos.second });
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first + 1, pos.second + 1 });
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first, pos.second + 1 });
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first - 1, pos.second + 1});
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first - 1, pos.second });
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first - 1, pos.second - 1 });
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first, pos.second - 1});
		sum += iter != mem.end() ? iter->second : 0;

		iter = mem.find({ pos.first + 1, pos.second - 1 });
		sum += iter != mem.end() ? iter->second : 0;

		mem[ pos ] = sum;
	}

	std::cout << "Value: " << mem[ pos ] << std::endl;
	return 0;
}