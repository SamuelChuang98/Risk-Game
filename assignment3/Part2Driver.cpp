#include <iostream>
#include <cstring>

#include "CommandProcessing.h"
#include "LogObserver.h"

using namespace std;

int main(int argc, char *argv[]) {

    GameState gs;
    GameEngine game = GameEngine(&gs);

    CommandProcessor* cmdProc;
    cmdProc = new CommandProcessor(gs);

    // Get every command...
    Command c = cmdProc->getCommand();

    if (!c.tournament.maps.empty()){
        game.startTournament(c.tournament.maps, c.tournament.strats,
                             c.tournament.games, c.tournament.turns);
    }

    return 0;
}
