#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "GameEngine.h"

using namespace std;


// Command stores commands as an aggregate structure with a name and effect
struct Command {
    void saveEffect(string str);    // Saves the effect of a command
    string name;
    string effect;
};

// Target; Processes game commands
class CommandProcessor {

private:

    vector<Command*> commands;  // Vector of commands saved
    GameState gs;

    virtual string readCommand();       // Read command from console
    void validate(Command& c);          // Validate a given command
    void saveCommand(string c_str);     // Save a command to commands vector

public:

    CommandProcessor(GameState& gs);
    ~CommandProcessor();

    Command getCommand();   // Get command object

};

// Adaptee of FileCommandProcessorAdapter
class FileLineReader {
public:
    FileLineReader(string file);
    string readLineFromFile();  // Reads and returns the next line
    bool isEof();   // Returns end-of-file status for this file
private:
    fstream fs;
};

// Adapts CommandProcessor to support reading files by line
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter(GameState &gs, string file);
private:
    string readCommand();   // Overwrite reads
    FileLineReader* flr;
};