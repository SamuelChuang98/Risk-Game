#include <iostream>
#include <string>
#include <vector>

#include "Map.h"

using namespace std;

// --------------------------------------------------------------------------------------------------------------
// PLAYER

//default constructor
Player::Player() {
    this->name = "No Name";
}

//Parameterized constructor
Player::Player(string pname) {
    this->name = pname;
}

//copy constructor
Player::Player(const Player &player) {
    this->name = player.name;
}

//Player assignment operator
Player& Player::operator=(const Player& player)
{
    this->name = player.name;
    return *this;
}

//destructor
Player::~Player() {

}

//player name accessor
string Player::getName() {
    return this->name;
}

//player name mutator
void Player::setName(string pname) {
    this->name = pname;
}

// --------------------------------------------------------------------------------------------------------------
// TERRITORY

// Default constructor
Territory::Territory() {
    this->territoryName = "None";
    this->continent = "None";
    this->numberOfArmies = 0;
    this->owner = new Player();
} 

// Copy constructor
Territory::Territory(Territory &t)
{
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    // this->playerName = t.playerName;
    this->numberOfArmies = t.numberOfArmies;
    this->owner = t.owner;
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
Map::Map(const Map &m) {
    this->territoryNum = m.territoryNum;
    this->adjMatrix = new bool[territoryNum * territoryNum];
    for (int i = 0; i < territoryNum * territoryNum; i++)
        this->adjMatrix[i] = m.adjMatrix[i];
}


// Parameterized constructor
Map::Map(int territoryNum) {
    this->territoryNum = territoryNum;
    adjMatrix = new bool* [territoryNum];
    for (int i = 0; i < territoryNum; i++)
        adjMatrix[i] = new bool[territoryNum]{false};
}


//Validate graph
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

