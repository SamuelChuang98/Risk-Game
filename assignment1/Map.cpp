#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Map.h"

using namespace std;

// --------------------------------------------------------------------------------------------------------------
// Territory

// Default constructor
Territory::Territory() {} 

// Copy constructor
Territory::Territory(Territory &t)
{
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    // this->playerName = t.playerName;
    this->numberOfArmies = t.numberOfArmies;
}

// Parameterized constructor
Territory::Territory(string territoryName, string continent, /* Player* playerName */ int numberOfArmies)
{
    this->territoryName = territoryName;
    this->continent = continent;
//  this->playerName = playerName;
    this->numberOfArmies = numberOfArmies;
}

// Territory assignment operator
Territory &Territory::operator= (const Territory &t)
{
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    // this->playerName = t.playerName;
    this->numberOfArmies = t.numberOfArmies;
    return *this;
}

// Territory stream insertion operator


// Territory Destructor
Territory::~Territory()
{

}

// Territory accessors

string Territory::getTerritoryName()
{
    return territoryName;
}

string Territory::getContinent()
{
    return continent;
}

/*
Player* Territory::getPlayerName()
{
    return playerName;
}
*/

int Territory::getNumberOfArmies()
{
    return numberOfArmies;
}

// Territory mutators

void Territory::setTerritoryName(string newTerritoryName)
{
    this->territoryName = newTerritoryName;
}

void Territory::setContinent(string newContinent)
{
    this->continent = newContinent;
}

/*
void Territory::setPlayerName(Player* newPlayerName)
{
    this->playerName = newPlayerName;
}
*/

void Territory::setNumberOfArmies(int newArmyCount)
{
    this->numberOfArmies = newArmyCount;
}

// Territory toString() method
std::string Territory::toString()  
{
    return getTerritoryName() + " " + getContinent() + " " + to_string(getNumberOfArmies());
}

// --------------------------------------------------------------------------------------------------------------
// Map 

// Default constructor 
Map::Map() {
    this -> territoryNum = 0;
    this -> adjMatrix = NULL;
}

// Copy constructor
Map::Map(Map &m)
{

}

// Parameterized constructor


//Validate graph if connected or not
bool Map::Validate() {
    bool visited[territoryNum];
    for (int j = 0; j < territoryNum; j++) {
        memset(visited, false, sizeof(visited));
        traverse(j, visited);
        for (int i = 0; i < territoryNum; i++){
            if (!visited[i]) return false;
        }
    }
    return true;
}

//traverses a graph
void Map::traverse(int j, bool visited[]) {
    visited[j] = true;
    for (int v = 0; v < territoryNum; v++){
        if (adjMatrix[j][v] && !visited[v]){
            traverse(v, visited);
        }
    }
}



// --------------------------------------------------------------------------------------------------------------
// MapLoader 

// Default constructor
MapLoader::MapLoader()
{
}

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

MapLoader& MapLoader::operator=(const MapLoader& m)
{
    this->fileName = m.fileName;
}

MapLoader::~MapLoader()
{
    delete fileName;
}

string* MapLoader::getFileName()
{
    return this->fileName;
}

void MapLoader::setFileName(string* fileName)
{
    this->fileName = fileName;
}

bool MapLoader::read()
{
    std::ifstream in;
    in.open(*fileName);

    while (in.good()) {

    }


    in.close();

    return false;
}

std::ostream& operator<<(std::ostream& strm, const MapLoader& m)
{
    return strm << "MapLoader(" << m.fileName << ")";
}


