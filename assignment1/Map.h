#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace mapSpace{
    int mapMain();
}

class Territory 
{
    private:
        // Private data members
        string territoryName;
        string continent;
        // Player* playerName;
        int numberOfArmies;

        // stream insertion operator
        friend std::ostream &operator<<(std::ostream &os, const Territory &t); 

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
    private:
        // Private data members
        

        // Stream insertion operator


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
       string* fileName;

       // Stream insertion operator
       friend std::ostream& operator<<(std::ostream& strm, const MapLoader& m);


    public:
        MapLoader();                                    // Default constructor
        MapLoader(const MapLoader &m);          // Copy constructor
        MapLoader(string* fileName);                     // Parameterized constructor
        MapLoader &operator= (const MapLoader &m);    // Assignment operator
        ~MapLoader();                                   // Destructor

        // Accessor
        string* getFileName();

        // Mutator
        void setFileName(string* fileName);    

        bool read();

};