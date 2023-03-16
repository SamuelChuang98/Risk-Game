#include "CommandProcessing.h"

#include <iostream>

using namespace std;

void Command::saveEffect(string str) {
    effect = str;
}

// TARGET - CommandProcessor //

CommandProcessor::CommandProcessor(GameState& gs) {
    this->gs = gs;
}

CommandProcessor::~CommandProcessor() {
    // Delete the dynamically allocated commands
    for(auto c : commands){
        delete c;
    }
    commands.clear();   // Clear the vector to avoid dangling pointers
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

void CommandProcessor::saveCommand(string c_str) {
    Command* c = new Command();
    c->name = c_str;
    commands.push_back(c);
    validate(*c);
}

Command CommandProcessor::getCommand() {
    string command = readCommand();
    saveCommand(command);
    return *commands.back();
}

// ADAPTEE - FileLineReader //

FileLineReader::FileLineReader(string file) {
    fs.open(file, ios::in);
}

string FileLineReader::readLineFromFile() {
    string str;
    getline(fs, str);
    return str;
}

bool FileLineReader::isEof() {
    return fs.eof();
}

// ADAPTER - FileCommandProcessorAdapter

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameState &gs, string file) : CommandProcessor(gs) {
    flr = new FileLineReader(file);
}

string FileCommandProcessorAdapter::readCommand() {
    return flr->readLineFromFile();
}