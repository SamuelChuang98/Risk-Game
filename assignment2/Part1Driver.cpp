#include <iostream>
#include <cstring>

#include "CommandProcessing.h"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "CommandProcessingDriver STARTED" << endl;

    CommandProcessor* cmdProc;
    GameState gs;

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

    // Get every command, and randomly save an effect to some commands
    while(true) {
        Command c = cmdProc->getCommand();
        if (c.name.empty()) break;
        if ((rand() % 100) > 50 && c.effect.empty())
            c.saveEffect("test effect");
        cout << c.name << " | " << c.effect << endl;
    }

    return 0;
}
