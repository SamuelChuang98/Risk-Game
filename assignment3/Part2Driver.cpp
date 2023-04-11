#include <iostream>
#include <cstring>

#include "CommandProcessing.h"
#include "LogObserver.h"

using namespace std;

int main(int argc, char *argv[]) {

    GameState gs;
    GameEngine game = GameEngine(&gs);

    CommandProcessor* cmdProc;

    // Will assign a CommandProcessor or FileCommandProcessorAdapter
    // depending on command-line arguments
    for(int i = 0; ; i++){
        if (strcmp(argv[i], "-console") == 0){
            cmdProc = new CommandProcessor(gs);
            break;
        }
            // If at last arg, -file is not possible. Default to console.
        else if (i == argc - 1){
            cmdProc = new CommandProcessor(gs);
            break;
        }
        else if ((strcmp(argv[i], "-file") == 0)){
            cmdProc = new FileCommandProcessorAdapter(gs, argv[i + 1]);
            break;
        }
    }

    // Get first command - Assumes there is only one command
    Command c = cmdProc->getCommand();

    if (!c.tournament.maps.empty()){
        game.startTournament(c.tournament.maps, c.tournament.strats,
                             c.tournament.games, c.tournament.turns);
    }

    return 0;
}
