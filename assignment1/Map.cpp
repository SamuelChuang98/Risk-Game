#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Map.h"

using namespace std;

// --------------------------------------------------------------------------------------------------------------
// Player (temporary)

// default constructor
TemporaryPlayer::TemporaryPlayer() {
    this->name = "No Name";
}

// copy constructor
TemporaryPlayer::TemporaryPlayer(const TemporaryPlayer &TemporaryPlayer) {
    this->name = TemporaryPlayer.name;
}

// Parameterized constructor
TemporaryPlayer::TemporaryPlayer(string pname) {
    this->name = pname;
}

// Assignment operator
TemporaryPlayer &TemporaryPlayer::operator=(const TemporaryPlayer &TemporaryPlayer)
{
    this->name = TemporaryPlayer.name;
    return *this;
}

// Destructor
TemporaryPlayer::~TemporaryPlayer() {}

// Accessor
string TemporaryPlayer::getName() {
    return this->name;
}

// Mutator
void TemporaryPlayer::setName(string pname) {
    this->name = pname;
}

// --------------------------------------------------------------------------------------------------------------
// Territory

// Default constructor
Territory::Territory() {
    this->territoryName = "None";
    this->continent = "None";
    this->numberOfArmies = 0;
    this->playerName = new TemporaryPlayer();
}

// Copy constructor
Territory::Territory(Territory &t)
{
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    this->playerName = t.playerName;
    this->numberOfArmies = t.numberOfArmies;
}

// Parameterized constructor
Territory::Territory(string territoryName, string continent, TemporaryPlayer* playerName, int numberOfArmies)
{
    this->territoryName = territoryName;
    this->continent = continent;
    this->playerName = playerName;
    this->numberOfArmies = numberOfArmies;
}

// Territory assignment operator
Territory &Territory::operator= (const Territory &t)
{
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    this->playerName = t.playerName;
    this->numberOfArmies = t.numberOfArmies;
    return *this;
}

// Territory stream insertion operator
std::ostream &operator<<(ostream &os, const Territory &t) {
    return os << "Territory(" << t.territoryName << t.continent << t.playerName << t.numberOfArmies << ")";
}

// Territory destructor
Territory::~Territory()
{
    delete playerName;
    // playerName.clear();
    playerName = NULL;
}

// Territory accessors
string Territory::getTerritoryName() { return territoryName; }
string Territory::getContinent() { return continent; }
TemporaryPlayer* Territory::getPlayerName() { return playerName; }
int Territory::getNumberOfArmies() { return numberOfArmies; }

// Territory mutators
void Territory::setTerritoryName(string newTerritoryName) { this->territoryName = newTerritoryName; }
void Territory::setContinent(string newContinent) { this->continent = newContinent; }
void Territory::setPlayerName(TemporaryPlayer* newPlayerName) { this->playerName = newPlayerName; }
void Territory::setNumberOfArmies(int newArmyCount) { this->numberOfArmies = newArmyCount; }

// Territory toString() method
std::string Territory::toString()
{
    return getTerritoryName() + " " + getContinent() + " " + to_string(getNumberOfArmies());
}

// --------------------------------------------------------------------------------------------------------------
// Map 

// Default constructor 
Map::Map() {
    this->territoryNumber = 0;
    std::vector<std::vector<int>> adjMatrix;
}

// Copy constructor
Map::Map(const Map &m) {
    this->territoryNumber = m.territoryNumber;
    this->adjMatrix = m.adjMatrix;
}


// Parameterized constructor
Map::Map(int territoryNumber) {
    this->territoryNumber = territoryNumber;
    adjMatrix.resize(territoryNumber, vector<int>(territoryNumber, 0));
}



// Assignment operator
Map &Map::operator= (const Map &m)
{
    this->territoryNumber = m.territoryNumber;
    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& strm, const Map& m)
{
    return strm << "Map(" << m.territoryNumber << ")";
}

// Destructor
Map::~Map()
{
    adjMatrix.clear();
}

// Method to add an edge
void Map::addEdge(int i, int j)
{
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;
}

// Method to remove an edge
void Map::removeEdge(int i, int j)
{
    adjMatrix[i][j] = 0;
    adjMatrix[j][i] = 0;
}


void Map::toString() {
    for (int i = 0; i < territoryNumber; i++) {
        for (int j = 0; j < territoryNumber; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Validates graph
/*
bool Map::Validate() {
    bool visited[territoryNumber];
    for (int j = 0; j < territoryNumber; j++) {
        // memset(visited, false, sizeof(visited));
        Traverse(j, visited);
        for (int i = 0; i < territoryNumber; i++){
            if (!visited[i]) return false;
        }
    }
    return true;
}
*/

// Traverses a graph
void Map::Traverse(int j, bool visited[]) {
    visited[j] = true;
    for (int v = 0; v < territoryNumber; v++){
        if (adjMatrix[j][v] && !visited[v]){
            Traverse(v, visited);
        }
    }
}

// --------------------------------------------------------------------------------------------------------------
// MapLoader

// Default constructor
MapLoader::MapLoader() {}

// Copy constructor
MapLoader::MapLoader(const MapLoader& m)
{
    this->fileName = new string(*m.fileName);
}

// Param. constructor
MapLoader::MapLoader(string* fileName)
{
    this->fileName = fileName;
}

// Assignment operator
MapLoader &MapLoader::operator= (const MapLoader& mL)
{
    this->fileName = mL.fileName;
    return *this;
}

// Destructor
MapLoader::~MapLoader()
{
    delete fileName;
}

// Accessor
string* MapLoader::getFileName()
{
    return this->fileName;
}

// Mutator
void MapLoader::setFileName(string* fileName)
{
    this->fileName = fileName;
}

// Validate File
bool MapLoader::read()
{

    Map* map = new Map();

    std::ifstream in;

    in.open(*fileName);
    bool valid = false;
    string line;

    int sectionsFound = 0;

    // Check if file contains countries (territories)
    while(getline(in, line)) {

        // Assumes a valid file will have continents, countries, then borders.
        if (line.find("[continents]") != string::npos) {

            while (true) {

                getline(in, line);

                // Break out if at end of continents
                if (line == "") {
                    break;
                }

                const int lineValues = 3;
                string lineSplit[lineValues]; // name, army value, color

                // Break values of continent into array
                for (int i = 0; i < lineValues; i++) {
                    int index = line.find(' '); // Index of first space
                    lineSplit[i] = line.substr(0, index);
                    line = line.substr(index);  // Remove first value from line
                }

                // Only continent name is currently important
                continents.push_back(new string(lineSplit[0]));
            }
            sectionsFound++;
        }
        else if (line.find("[countries]") != string::npos) {

            while (true) {

                getline(in, line);

                // Break out if at end of countries
                if (line == "") {
                    break;
                }

                const int lineValues = 5;
                string lineSplit[lineValues]; // num, name, continent index, x, y



                // Break values of country into array
                for (int i = 0; i < lineValues; i++) {
                    int index = line.find(' ');
                    lineSplit[i] = line.substr(0, index);
                    line = line.substr(index+1);
                }

                int continentIndex = stoi(lineSplit[2])-1;
                string* continent = continents.at(continentIndex);

                Territory* t = new Territory();
                t->setTerritoryName(lineSplit[1]);
                t->setContinent(*continent);
                territories.push_back(t);
            }
            sectionsFound++;
        }
        else if (line.find("[borders]") != string::npos) {

            while (true) {

                getline(in, line);

                // Break out if at end of borders
                if (line == "") {
                    break;
                }

                int targetCountryIndex = 0;
                vector<int*> adjacentIndexes;

                // Break values of country into array
                int counter = 0;
                while (line.find(' ') != string::npos) {
                    int delimiterIndex = line.find(' ');
                    int countryIndex = stoi(line.substr(0, delimiterIndex));
                    if (counter == 0) {
                        // First value is a country that has adjacent countries
                        targetCountryIndex = countryIndex;
                    }
                    else {
                        // Proceeding values are indexes of adjacent the countries
                        // Add all the adjacent country indexes to adj matrix of target country
                        map->addEdge(targetCountryIndex, countryIndex);
                        line = line.substr(delimiterIndex+1);
                    }
                    counter++;
                }
            }
            sectionsFound++;
        }
        valid = (sectionsFound == 3);
    }
    in.close();

    // Exit if file is invalid
    if(!valid) {
        cout << "Invalid File";
        exit(0);
    }

    return valid;
}

// Fetch territories list in a .map file
void MapLoader::getTerritoriesFromFile()
{
    string line;
    std::ifstream in;
    in.open(*fileName);

    getline(in, line);

    while(!in.eof()) {

    }
}

// Stream assignment operator
std::ostream& operator<<(std::ostream& strm, const MapLoader& mL)
{
    return strm << "MapLoader(" << mL.fileName << ")";
}