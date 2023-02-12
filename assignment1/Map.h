#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
namespace mapSpace{
    int mapMain();
}

// Temporary Player class
class Player
{
    private:
        // Private data member
        string name;

    public:
        Player();                               // Default constructor
        Player(const Player &p);                // Copy constructor
        Player(string pname);                   // Parameterized constructor
        Player &operator= (const Player &p);    // Assignment operator
        ~Player();                              // Destructor

        // Accessor
        string getName();

        // Mutator
        void setName(string pname); 
};

class Territory 
{
    private:
        // Private data members
        string territoryName;
        string continent;
        Player* playerName;
        int numberOfArmies;

        // stream insertion operator
        friend std::ostream &operator<<(std::ostream &os, const Territory &t); 

    public:
        Territory();                                                                                     // Default constructor
        Territory(Territory &territory);                                                                 // Copy constructor
        Territory(string territoryName, string continent, Player* playerName, int numberOfArmies);       // Parameterized constructor
        Territory &operator= (const Territory &t);                                                       // Assignment operator
        ~Territory();                                                                                    // Destructor

        // Accessors
        string getTerritoryName();
        string getContinent();
        Player* getPlayerName();
        int getNumberOfArmies();
            
        // Mutators
        void setTerritoryName(string newName);
        void setContinent(string newContinent);
        void setPlayerName(Player* newPlayerName);
        void setNumberOfArmies(int newArmyCount);

        // toString() method
        std::string toString();
};

class Map
{
    private:
        // Private data members
        int territoryNumber;

        // Stream insertion operator
        friend std::ostream &operator<<(std::ostream &os, const Map &m); 

    public:
        Map();                          // Default constructor
        Map(const Map &m);              // Copy constructor
        Map(int territoryNumber);       // Parameterized constructor
        Map &operator= (const Map &m);  // Assignment operator
        ~Map();                         // Destructor

        // Method to add an edge to the adjacency matrix
        void addEdge(int i, int j);
        
        // Method to remove an edge from the adjacency matrix
        void removeEdge(int i, int j);
        
        // Validate method
        bool Validate();

        // Traverse method
        void Traverse(int j, bool visited[]);

};

class MapLoader
{
    private:
       // Private data member 
       string* fileName;

       // Stream insertion operator
       friend std::ostream& operator<<(std::ostream& strm, const MapLoader& mL);

    public:
        MapLoader();                                // Default constructor
        MapLoader(const MapLoader &m);              // Copy constructor
        MapLoader(string* fileName);                // Parameterized constructor
        MapLoader &operator= (const MapLoader &m);  // Assignment operator
        ~MapLoader();                               // Destructor

        // Accessor
        string* getFileName();

        // Mutator
        void setFileName(string* fileName);    

        bool read(); // Check if file is valid

        void getTerritoriesFromFile(); // Get the territories from valid files



};