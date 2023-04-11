#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "GameEngine.h"
#include "Subject.h"
#include "ILoggable.h"

using namespace std;

// Command stores commands as an aggregate structure with a name and effect
struct Command : public Subject, public ILoggable{
    void saveEffect(string str);    // Saves the effect of a command
    void StringTolog() override;
    string name;
    string effect;
};

// Target; Processes game commands
class CommandProcessor : public Subject, public ILoggable {

private:
    virtual string readCommand();           // Read command from console
    void validate(Command& c);              // Validate a given command
    string validateTournament(Command& c);  // Validate a given tournament command
    void saveCommand(string c_str);         // Save a command to commands vector
    friend std::ostream &operator<<(std::ostream &strm, const CommandProcessor &p); // stream insertion operator


protected:
    vector<Command*> commands;  // Vector of commands saved
    GameState gs;

public:
    CommandProcessor(GameState& gs);
    ~CommandProcessor();
    CommandProcessor(CommandProcessor &c);     // Copy constructor
    CommandProcessor &operator=(const CommandProcessor &rightSide);    // Assignment operator
    Command getCommand();   // Get command object
    void StringTolog() override;

};

// Adaptee of FileCommandProcessorAdapter
class FileLineReader {
public:
    FileLineReader(string file);
    FileLineReader(FileLineReader &c);     // Copy constructor
    FileLineReader &operator=(const FileLineReader &rightSide);    // Assignment operator
    string readLineFromFile();  // Reads and returns the next line
    bool isEof();   // Returns end-of-file status for this file

private:
    string file;
    fstream fs;
    friend std::ostream &operator<<(std::ostream &strm, const FileLineReader &p); // stream insertion operator
};

// Adapts CommandProcessor to support reading files by line
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter(GameState &gs, string file);
    FileCommandProcessorAdapter(FileCommandProcessorAdapter &c);     // Copy constructor
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &rightSide);    // Assignment operator

private:
    string readCommand();   // Overwrite reads
    FileLineReader* flr;
    friend std::ostream &operator<<(std::ostream &strm, const FileCommandProcessorAdapter &p); // strm insertion op
};