#include <iostream>
#include <string>
#include <vector>

// #pragma once

using namespace std;

class Territory 
{
    // Private data members
    private:
        string territoryName;
        string continent;
        // Player* playerName;
        int numberOfArmies;

    public:
        Territory();                                                                                     // Default constructor
        Territory(Territory &territory);                                                                 // Copy constructor
        Territory(string territoryName, string continent, /* Player* playerName, */ int numberOfArmies); // Parameterized constructor
                                                                                                         // Assignment operator
                                                                                                         // Stream insertion operator
        ~Territory();                                                                                    // Destructor

        // Accessors
        string getTerritoryName();
        string getContinent();
        // Player* getPlayerName();
        int getNumberOfArmies();
            
        // Mutators
        void setTerritoryName(string newName);
        void setContinent(string newContinent);
        // void setPlayerName(Player* newPlayerName);
        void setNumberOfArmies(int newArmyCount);

    // toString() method
    std::string toString();
};

class Map
{
    private:


    public:
        Map();          // Default constructor
        Map(Map &map);  // Copy constructor
                        // Parameterized constructor
                        // Assignment operator
        ~Map();         // Destructor

};

class MapLoader
{

};