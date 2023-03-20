#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Player.h"

using namespace std;

namespace mapSpace {
    int mapMain();
}


class Continent
{
private:
    string continentName;
    int armyNumber;
    string color;
public:
    Continent();
    Continent(string continentName, int armyNumber, string color);
    ~Continent();

    string getContinentName();
    int getArmyNumber();
    string getColor();

    void setContinentName(string continentName);
    void setArmyNumber(int armyNumber);
    void setColor(string color);

    friend std::ostream& operator<<(std::ostream& os, const Continent& c);

};

class Territory
{
private:
    // Private data members
    int territoryNumber;
    string territoryName;
    int continent;
    int x;
    int y;
    Player* player;
    int numberOfArmies;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Territory& t);

public:
    Territory();                                                                                     // Default constructor
    Territory(Territory& territory);                                                                 // Copy constructor
    Territory(int territoryNumber,string territoryName, int continent,int x,int y, Player* player, int numberOfArmies);       // Parameterized constructor
    //Territory(int territoryNumber, string territoryName, int continent, int x, int y, int numberOfArmies);
    Territory& operator= (const Territory& t);                                                       // Assignment operator
    ~Territory();                                                                                    // Destructor
    
    // Accessors
    int getTerritoryNumber();
    string getTerritoryName();
    int getContinent();
    int getX();
    int getY();
    Player* getPlayer();
    int getNumberOfArmies();

    // Mutators
    void setTerritoryNumber(int newNumber);
    void setTerritoryName(string newName);
    void setContinent(int newContinent);
    void setX(int x);
    void setY(int y);
    void setPlayer(Player* newPlayer);
    void setNumberOfArmies(int newArmyCount);
};

class Map
{
private:
    // Private data members
    vector<Continent*> continents;
    vector<vector<int>> borders;
    vector<Territory*> territories;

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Map& m);

public:
    Map();                          // Default constructor
    Map(const Map& m);              // Copy constructor
    Map(vector<Continent*> continents, vector<Territory*> territories, vector<vector<int>> borders);       // Parameterized constructor
    Map& operator= (const Map& m);  // Assignment operator
    ~Map();                         // Destructor

    // Method to add an edge to the adjacency matrix
    void addBorder(vector<int> border);
    void addContinent(Continent* continent);
    void addTerritory(Territory* territory);

    // Validate method
    bool Validate();

    // Load continents, countries and borders to map
    void mapLoad(string fileName);

    //Mutators
    void setContinents(vector<Continent*> continents);
    void setBorders(vector<vector<int>> borders);
    void setTerritories(vector<Territory*> territories);

    //Accessors
    vector<Continent*> getContinents();
    vector<vector<int>> getBorders();
    vector<Territory*> getTerritories();
};

class MapLoader
{
private:
    // Private data member 
    string fileName;

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& strm, const MapLoader& mL);

public:
    MapLoader();                                // Default constructor
    MapLoader(const MapLoader& m);              // Copy constructor
    MapLoader(string fileName);                 // Parameterized constructor
    MapLoader& operator= (const MapLoader& m);  // Assignment operator
    ~MapLoader();                               // Destructor

    // Check if file is valid
    bool fileChecker();

    // Accessor
    string getFileName();

    // Mutator
    void setFileName(string fileName);
};