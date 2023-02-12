#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Map.h"

using namespace std;

// --------------------------------------------------------------------------------------------------------------
// Player (temporary)

// default constructor
Player::Player() {
    this->name = "No Name";
}

// copy constructor
Player::Player(const Player &player) {
    this->name = player.name;
}

// Parameterized constructor
Player::Player(string pname) {
    this->name = pname;
}

// Assignment operator
Player &Player::operator=(const Player &player)
{
    this->name = player.name;
    return *this;
}

// Destructor
Player::~Player() {}

// Accessor
string Player::getName() {
    return this->name;
}

// Mutator
void Player::setName(string pname) {
    this->name = pname;
}

// --------------------------------------------------------------------------------------------------------------
// Territory

// Default constructor
Territory::Territory() {
    this->territoryName = "None";
    this->continent = "None";
    this->numberOfArmies = 0;
    this->playerName = new Player();
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
Territory::Territory(string territoryName, string continent, Player* playerName, int numberOfArmies)
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
Player* Territory::getPlayerName() { return playerName; }
int Territory::getNumberOfArmies() { return numberOfArmies; }

// Territory mutators
void Territory::setTerritoryName(string newTerritoryName) { this->territoryName = newTerritoryName; }
void Territory::setContinent(string newContinent) { this->continent = newContinent; }
void Territory::setPlayerName(Player* newPlayerName) { this->playerName = newPlayerName; }
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
    // this->adjMatrix = NULL;
}

// Copy constructor
Map::Map(const Map &m) {
    this->territoryNumber = m.territoryNumber;
    // this->adjMatrix = new bool[territoryNum * territoryNum];
    // for (int i = 0; i < territoryNum * territoryNum; i++)
    //     this->adjMatrix[i] = m.adjMatrix[i];
}

// Parameterized constructor
Map::Map(int territoryNumber) {
    this->territoryNumber = territoryNumber;
    // adjMatrix = new bool* [territoryNumber];
    // for (int i = 0; i < territoryNumber; i++)
    //     adjMatrix[i] = new bool[territoryNumber]{false};
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

}

// Method to add an edge 
void addEdge(int i, int j)
{

}

// Method to remove an edge
void removeEdge(int i, int j)
{

}

//Validate graph 
bool Map::Validate() {
    bool visited[territoryNumber];
    for (int j = 0; j < territoryNumber; j++) {
        // memset(visited, 0, sizeof(visited));W
        Traverse(j, visited);
        for (int i = 0; i < territoryNumber; i++){
            if (!visited[i]) return false;
        }
    }
    return true;
}

//traverses a graph
void Map::Traverse(int j, bool visited[]) {
    visited[j] = true;
    for (int v = 0; v < territoryNumber; v++){
        if (/*adjMatrix[j][v] && */ !visited[v]){
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

//
bool MapLoader::read()
{
    std::ifstream in;
    in.open(*fileName);

    while (in.good()) {

    }

    in.close();

    return false;
}

// Stream assignment operator
std::ostream& operator<<(std::ostream& strm, const MapLoader& mL)
{
    return strm << "MapLoader(" << mL.fileName << ")";
}

