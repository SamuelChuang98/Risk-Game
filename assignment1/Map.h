#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Territory 
{
    private:
        // Private data members
        string territoryName;
        string continent;
        // Player* playerName;
        int numberOfArmies;

        // stream insertion operator

    public:
        Territory();                                                                                     // Default constructor
        Territory(Territory &territory);                                                                 // Copy constructor
        Territory(string territoryName, string continent, /* Player* playerName, */ int numberOfArmies); // Parameterized constructor
        Territory &operator= (const Territory &t);                                                       // Assignment operator
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
    // Private data members
    private:
    

    public:
        Map();                          // Default constructor
        Map(Map &map);                  // Copy constructor
                                        // Parameterized constructor
        Map &operator= (const Map &m);  // Assignment operator
        ~Map();                         // Destructor

};

class MapLoader
{
    private:
       // Private data member 
       string fileName;

       // Stream insertion operator

    public:
        MapLoader();                                    // Default constructor
        MapLoader(const MapLoader &MapLoader);          // Copy constructor
        MapLoader(string fileName);                     // Parameterized constructor
        MapLoader &operator= (const Map &MapLoader);    // Assignment operator
        ~MapLoader();                                   // Destructor

        // Accessor
        string getFileName();

        // Mutator
        void setFileName(string fileName);    

};