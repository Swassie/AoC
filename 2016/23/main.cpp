#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

enum opCode { CPY, INC, DEC, JNZ, TGL };
enum addrMode { REG, REGREG, LITREG, REGLIT };

int main() {

	std::ifstream fileStream{ "../input.txt" };
	std::string tempString;
	int registers[]{ 12, 0, 0, 0 };
	std::vector< std::array< int, 4 > > instructions;
	int curInstruction{ 0 };

	while( std::getline( fileStream, tempString )) {
		std::array< int, 4 > instr;
		std::istringstream instrStream{ tempString };

		instrStream >> tempString;

		if( tempString == "cpy" ) {
			std::string src;
			char dst;
			instr[ 0 ] = CPY;

			instrStream >> src;
			instrStream >> dst;

			if( std::isdigit( src.back() )) {
				instr[ 1 ] = LITREG;
				instr[ 2 ] = std::stoi( src );
			}
			else {
				instr[ 1 ] = REGREG;
				instr[ 2 ] = src[0] - 'a';
			}
			instr[ 3 ] = dst - 'a';
		}
		else if( tempString == "inc" ) {
			char reg;
			instrStream >> reg;

			instr[ 0 ] = INC;
			instr[ 1 ] = REG;
			instr[ 2 ] = reg - 'a';
		}
		else if( tempString == "dec" ) {
			char reg;
			instrStream >> reg;

			instr[ 0 ] = DEC;
			instr[ 1 ] = REG;
			instr[ 2 ] = reg - 'a';
		}
		else if( tempString == "jnz" ) {
			std::string condString, offset;
			instr[ 0 ] = JNZ;

			instrStream >> condString;
			instrStream >> offset;

			if( std::isdigit( condString.back() ) && !std::isdigit( offset.back() ) ) {
				instr[ 1 ] = LITREG;
				instr[ 2 ] = std::stoi( condString );
				instr[ 3 ] = offset[ 0 ] - 'a';
			}
			else if( !std::isdigit( condString.back() ) && std::isdigit( offset.back() ) ) {
				instr[ 1 ] = REGLIT;
				instr[ 2 ] = condString[ 0 ] - 'a';
				instr[ 3 ] = std::stoi( offset );
			}
		}
		else if( tempString == "tgl" ) {
			char reg;
			instr[ 0 ] = TGL;
			instr[ 1 ] = REG;

			instrStream >> reg;
			instr[ 2 ] = reg - 'a';
		}
		instructions.push_back( instr );
	}

	while( curInstruction < instructions.size() ) {
		std::array< int, 4 > instr( instructions[ curInstruction ] );

		switch( instr[ 0 ] ){
			case CPY:
				switch( instr[ 1 ] ){
					case REGREG:
						registers[ instr[ 3 ] ] = registers[ instr[ 2 ] ];
						break;
					case LITREG:
						registers[ instr[ 3 ] ] = instr[ 2 ];
						break;
					default:
						break;
				}
				break;
			case INC:
				switch( instr[ 1 ] ){
					case REG:
						registers[ instr[ 2 ] ]++;
						break;
					default:
						break;
				}
				break;
			case DEC:
				switch( instr[ 1 ] ){
					case REG:
						registers[ instr[ 2 ] ]--;
						break;
					default:
						break;
				}
				break;
			case JNZ:
				switch( instr[ 1 ] ){
					case LITREG:
						if( instr[ 2 ] ){
							curInstruction += registers[ instr[ 3 ] ];
							continue;
						}
						break;
					case REGLIT:
						if( registers[ instr[ 2 ] ] ){
							curInstruction += instr[ 3 ];
							continue;
						}
						break;
					default:
						break;
				}
				break;
			case TGL:
				switch( instr[ 1 ] ){
					case REG: {
						int tglInstr{ curInstruction + registers[ instr[ 2 ] ] };

						if ( tglInstr > 0 && tglInstr < instructions.size()) {
							switch ( instructions[ tglInstr ][ 0 ] ) {
								case INC:
									instructions[ tglInstr ][ 0 ] = DEC;
									break;
								case DEC:
								case TGL:
									instructions[ tglInstr ][ 0 ] = INC;
									break;
								case CPY:
									instructions[ tglInstr ][ 0 ] = JNZ;
									break;
								case JNZ:
									instructions[ tglInstr ][ 0 ] = CPY;
									break;
								default:
									return -1;
							}
						}
						break;
					}
					default:
						break;
				}
				break;
			default:
				return -1;
		}
		curInstruction++;
	}

	std::cout << "Register a: " << registers[ 0 ];
	return 0;
}