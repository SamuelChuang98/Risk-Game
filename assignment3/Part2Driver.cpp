#include <iostream>
#include <cstring>

#include "CommandProcessing.h"
#include "LogObserver.h"

using namespace std;

int main(int argc, char *argv[]) {

    GameState gs;
    CommandProcessor* cmdProc;
    cmdProc = new CommandProcessor(gs);

    // Get every command, and randomly save an effect to some commands
    Command c = cmdProc->getCommand();

    return 0;
}
