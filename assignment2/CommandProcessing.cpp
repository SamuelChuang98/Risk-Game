#include "CommandProcessing.h"

#include <iostream>

using namespace std;

// COMMAND //

void Command::saveEffect(string str) {
    effect = str;
    Notify(this);
}

void Command::StringTolog() {
    ofstream output;
    output.open("log.txt", ios::app);
    if (output.is_open()){
        output << "CommandProcessor saveEffect(): " << effect << endl;
        output.close();
    }
    else{
        cerr << "unable to open output file" << endl;
    }
    output.close();
}

// TARGET - CommandProcessor // ------------------------------------------

// Param. constructor
CommandProcessor::CommandProcessor(GameState& gs) {
    this->gs = gs;
}

// Destructor
CommandProcessor::~CommandProcessor() {
    // Delete the dynamically allocated commands
    for(auto c : commands){
        delete c;
    }
    commands.clear();   // Clear the vector to avoid dangling pointers
}

// Copy constructor - performs deep copy
CommandProcessor::CommandProcessor(CommandProcessor &c) {
    for (Command *command: c.commands) {
        this->commands.push_back(new Command(*command));
    }
    this->gs = GameState(gs);
}

// Prompt for and read a command through console
string CommandProcessor::readCommand() {
    string s;
    cout << "Enter command: ";
    getline(cin, s);
    cout << endl;
    return s;
}

// Validate a command by checking command name and current state. Invalid commands
// receive effects that correspond to the error
void CommandProcessor::validate(Command &c) {

    // First part of command is needed (e.g. "loadmap" from "loadmap example.map")
    string initial_command;
    size_t space_pos = c.name.find(' ');    // Find the first space in command name
    if (space_pos == string::npos)
        initial_command = c.name;
    else
        initial_command = c.name.substr(0, space_pos);

    string currentState = gs.getGameState();

    if (initial_command == "loadmap"){
        if (currentState != "start" && currentState != "maploaded")
            c.saveEffect("Error: loadmap must have state start or maploaded");
    }
    else if (initial_command == "validatemap"){
        if (currentState != "maploaded")
            c.saveEffect("Error: validatemap must have state maploaded");
    }
    else if (initial_command == "addplayer"){
        if (currentState != "mapvalidated" && currentState != "playersadded")
            c.saveEffect("Error: addplayer must have state mapvalidated or playersadded");
    }
    else if (initial_command == "gamestart"){
        if (currentState != "playersadded")
            c.saveEffect("Error: gamestart must have state playersadded");
    }
    else if (initial_command == "replay"){
        if (currentState != "win")
            c.saveEffect("Error: quit must have state win");
    }
    else if (initial_command == "quit"){
        if (currentState != "win")
            c.saveEffect("Error: quit must have state win");
    }
    else{
        c.saveEffect("Error: invalid command");
    }

}

// Saves a command to a commands vector
void CommandProcessor::saveCommand(string c_str) {
    Command* c = new Command();
    c->name = c_str;
    commands.push_back(c);
    Notify(this);
    validate(*c);
}


// Stream insertion operator
std::ostream &operator<<(std::ostream &strm, const CommandProcessor &c){
    return strm << c.commands.back()->name;
}

// Assignment operator - performs shallow copy
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &rightSide) {
    this->commands = rightSide.commands;
    this->gs = rightSide.gs;
    return *this;
}

// Returns last command object
Command CommandProcessor::getCommand() {
    string command = readCommand();
    saveCommand(command);
    return *commands.back();
}

void CommandProcessor::StringTolog() {
    ofstream output;
    output.open("log.txt", ios::app);
    if (output.is_open()){
        Command* lastCommand = commands.back();
        output << "CommandProcessor saveCommand(): " << lastCommand->name << endl;
        output.close();
    }
    else{
        cerr << "unable to open output file" << endl;
    }
    output.close();
}

// ADAPTEE - FileLineReader // -------------------------------------------

// Param. constructor
FileLineReader::FileLineReader(string file) {
    this->file = file;
    fs.open(file, ios::in);
}

// Copy constructor
FileLineReader::FileLineReader(FileLineReader &c) {
    this->file = c.file;
    fs.open(c.file, ios::in);
}

// Assignment operator
FileLineReader &FileLineReader::operator=(const FileLineReader &rightSide){
    this->file = rightSide.file;
    fs.open(rightSide.file, ios::in);
    return *this;
}

// Reads and returns the next line in file
string FileLineReader::readLineFromFile() {
    string str;
    getline(fs, str);
    return str;
}

// Returns end-of-file status for this file
bool FileLineReader::isEof() {
    return fs.eof();
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &strm, const FileLineReader &flr){
    return strm << flr.file;
}

// ADAPTER - FileCommandProcessorAdapter // ------------------------------

// Param. constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameState &gs, string file) : CommandProcessor(gs) {
    flr = new FileLineReader(file);
}

// Copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter &c) : CommandProcessor(c) {
    for (Command *command: c.commands) {
        this->commands.push_back(new Command(*command));
    }
    this->gs = GameState(gs);
    this->flr = c.flr;
}

// Assignment operator
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &rightSide) {
    this->commands = rightSide.commands;
    this->gs = rightSide.gs;
    this->flr = rightSide.flr;
    return *this;
}

// Overwrite reads file line by line instead of retrieving user-input
string FileCommandProcessorAdapter::readCommand() {
    return flr->readLineFromFile();
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &strm, const FileCommandProcessorAdapter &c){
    return strm << c.commands.back();
}
