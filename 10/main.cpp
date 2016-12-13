#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Bot.h"
#include "Bin.h"

int main() {

    std::ifstream fileStream{ "../input.txt" };
    std::string tempString;
    std::unordered_map< size_t, Bot * > bots;
    std::unordered_map< size_t, Bin * > bins;

    while( std::getline( fileStream, tempString )) {
        std::istringstream instruction{ tempString };

        instruction >> tempString;
        if( tempString == "value" ) {
            size_t microchip, botNr;
            instruction >> microchip;
            instruction.ignore( 13 );
            instruction >> botNr;
            Bot *&bot{ bots[ botNr ]};
            if( bot ) {
                bot->addMicrochip(microchip);
            }
            else {
                bot = new Bot{ botNr };
                bot->lookFor( 17, 61 );
                bot->addMicrochip(microchip);
            }
        }
        else if( tempString == "bot" ) {
            size_t botNr, low, high;
            instruction >> botNr;

            Bot *&bot{ bots[ botNr ]};
            if( !bot ) {
                bot = new Bot{ botNr };
                bot->lookFor( 17, 61 );
            }
            instruction.ignore( 14 );
            instruction >> tempString;
            instruction >> low;
            if( tempString == "bot" ) {
                Bot *&lowBot{ bots[ low ]};
                if( !lowBot ) {
                    lowBot = new Bot{ low };
                    lowBot->lookFor( 17, 61 );
                }
                bot->assignLow( lowBot );
            }
            else if( tempString == "output" ) {
                Bin *&lowBin{ bins[ low ]};
                if( !lowBin ) {
                    lowBin = new Bin;
                }
                bot->assignLow( lowBin );
            }
            instruction.ignore( 13 );
            instruction >> tempString;
            instruction >> high;
            if( tempString == "bot" ) {
                Bot *&highBot{ bots[ high ]};
                if( !highBot ) {
                    highBot = new Bot{ high };
                    highBot->lookFor( 17, 61 );
                }
                bot->assignHigh( highBot );
            }
            else if( tempString == "output" ) {
                Bin *&highBin{ bins[ high ]};
                if( !highBin ) {
                    highBin = new Bin;
                }
                bot->assignHigh( highBin );
            }
        }
    }

    bool newChanges{ true };
    while( newChanges ) {
        newChanges = false;
        for( auto &pair : bots ) {
            newChanges |= pair.second->update();
        }
    }

    std::cout << bins[0]->getMicrochips()[0] *
                 bins[1]->getMicrochips()[0] *
                 bins[2]->getMicrochips()[0];

    return 0;
}