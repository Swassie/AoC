#include <iostream>
#include <list>

void stealNext( std::list< size_t > &elves ) {
	while( elves.size() != 1 ) {
		std::list< size_t >::iterator it{ elves.begin() };
		bool removeFirst{ elves.size() % 2 == 1 };

		std::cout << "Elves left: " << elves.size() << std::endl;

		while ( it != elves.end() && ++it != elves.end()) {
			it = elves.erase( it );
		}

		if ( removeFirst ) {
			elves.erase( elves.begin());
		}
	}
}

void stealAcross( std::list< size_t > &elves ) {
	size_t skip{ elves.size() / 2 }, state{ elves.size() % 2 }, size{ elves.size() };
	std::list< size_t >::iterator it{ elves.begin() };

	while( skip > 0 ) {
		++it;
		--skip;
	}

	while( size > 1 ) {
		std::cout << "Elves left: " << size << std::endl;

		while( it != elves.end() && size > 1 ) {
			switch( state ) {
				case 0:
				case 1:
					it = elves.erase( it );
					--size;
					break;
				case 2:
					++it;
					break;
			}
			state = ++state % 3;
		}
		it = elves.begin();
	}
}

int main() {

	const size_t input{ 3018458 };
	std::list< size_t > elves( input );

	std::list< size_t >::iterator it{ elves.begin() };
	for( size_t i{ 0 }; i < input; ++i ) {
		*it = i + 1;
		++it;
	}

#if 0
	stealNext( elves );
#else
	stealAcross( elves );
#endif

	std::cout << "Last elf standing: " << elves.front();

	return 0;
}