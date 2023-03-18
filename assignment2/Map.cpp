#include "Map.h"

using namespace std;

// --------------------------------------------------------------------------------------------------------------
// Player (temporary)

// default constructor
TemporaryPlayer::TemporaryPlayer() {
    this->name = "No Name";
}

// copy constructor
TemporaryPlayer::TemporaryPlayer(const TemporaryPlayer& TemporaryPlayer) {
    this->name = TemporaryPlayer.name;
}

// Parameterized constructor
TemporaryPlayer::TemporaryPlayer(string pname) {
    this->name = pname;
}

// Assignment operator
TemporaryPlayer& TemporaryPlayer::operator=(const TemporaryPlayer& TemporaryPlayer)
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

std::ostream& operator<<(ostream& os, const TemporaryPlayer& t) {
    return os << t.name;
}

// --------------------------------------------------------------------------------------------------------------
// Territory

// Default constructor
Territory::Territory() {
    this->territoryNumber = 0;
    this->territoryName = "None";
    this->continent = 0;
    this->x = 0;
    this->y = 0;
    this->numberOfArmies = 0;
    this->player = nullptr;
}

// Copy constructor
Territory::Territory(Territory& t)
{
    this->territoryNumber = t.territoryNumber;
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    this->x = t.x;
    this->y = t.y;
    this->player = t.player;
    this->numberOfArmies = t.numberOfArmies;
}

// Parameterized constructor
Territory::Territory(int territoryNumber, string territoryName, int continent, int x, int y, TemporaryPlayer* player, int numberOfArmies)
{
    this->territoryNumber = territoryNumber;
    this->territoryName = territoryName;
    this->continent = continent;
    this->x = x;
    this->y = y;
    this->player = player;
    this->numberOfArmies = numberOfArmies;
}

// Territory assignment operator
Territory& Territory::operator= (const Territory& t)
{
    this->territoryNumber = t.territoryNumber;
    this->territoryName = t.territoryName;
    this->continent = t.continent;
    this->x = t.x;
    this->y = t.y;
    this->player = t.player;
    this->numberOfArmies = t.numberOfArmies;
    return *this;
}

// Territory stream insertion operator
std::ostream& operator<<(ostream& os, const Territory& t) {
    return os << "Number: " << t.territoryNumber << "\nName: " << t.territoryName << "\nContinent: " << t.continent << "\nx: " << t.x << "\ny: " << t.y  << "\nNumber of armies: " << t.numberOfArmies << endl;
}

// Territory destructor
Territory::~Territory()
{
    player = nullptr;
}

// Territory accessors
int Territory::getTerritoryNumber() { return territoryNumber; }
string Territory::getTerritoryName() { return territoryName; }
int Territory::getContinent() { return continent; }
int Territory::getX() { return x; }
int Territory::getY() { return y; }
TemporaryPlayer* Territory::getPlayerName() { return player; }
int Territory::getNumberOfArmies() { return numberOfArmies; }

// Territory mutators
void Territory::setTerritoryNumber(int newNumber) { this->territoryNumber = newNumber; }
void Territory::setTerritoryName(string newTerritoryName) { this->territoryName = newTerritoryName; }
void Territory::setContinent(int newContinent) { this->continent = newContinent; }
void Territory::setX(int x) { this->x = x; }
void Territory::setY(int y) { this->y = y; }
void Territory::setPlayerName(TemporaryPlayer* newPlayerName) { this->player = newPlayerName; }
void Territory::setNumberOfArmies(int newArmyCount) { this->numberOfArmies = newArmyCount; }

// --------------------------------------------------------------------------------------------------------------
// Map 

// Default constructor 
Map::Map() 
{ 
    
}

int Map::getNum() { return num; }
void Map::setNum(int n) { this->num = n; }

// Copy constructor
Map::Map(const Map& m) {
    this->continents = m.continents;
    this->borders = m.borders;
    this->territories = m.territories;
}


// Parameterized constructor
Map::Map(vector<string> continents, vector<Territory*> territories, vector<vector<int>> borders){
    this->continents = continents;
    this->borders = borders;
    this->territories = territories;
}

//Accessors
vector<string> Map::getContinents() { return this->continents; }
vector<vector<int>> Map::getBorders() { return this->borders; }
vector<Territory*> Map::getTerritories() { return this->territories; }

//Mutators
void Map::setContinents(vector<string> continents) { this->continents = continents; }
void Map::setBorders(vector<vector<int>> borders) { this->borders = borders; }
void Map::setTerritories(vector<Territory*> territories) { this->territories = territories; }

// Assignment operator
Map& Map::operator= (const Map& m)
{
    this->continents = m.continents;
    this->borders = m.borders;
    this->territories = m.territories;
    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& strm, const Map& m)
{

    int bordersNum = 0;
    for (int i = 0; i < m.borders.size(); i++)
    {
        for (int j = 1; j < m.borders[i].size(); j++)
        {
            bordersNum++;
        }
    }

    return strm << "Continents: " << m.continents.size() << "\nBorders: " << bordersNum << "\nTerritories: " << m.territories.size();
}

// Destructor
Map::~Map()
{
    for (int i = 0; i < this->territories.size(); i++) { delete territories[i]; }
}

// Method to add an edge
void Map::addBorder(vector<int> border)
{
    this->borders.push_back(border);
}

void Map::addContinent(string continent) 
{
    this->continents.push_back(continent);
}

void Map::addTerritory(Territory* territory)
{
    this->territories.push_back(territory);
}


// Validates graph
//bool Map::Validate(){
//    vector<bool> visited(this->territoryNumber);
//    for (int j = 0; j < territoryNumber; j++) {
//        // memset(visited, false, sizeof(visited));
//        Traverse(j, visited);
//        for (int i = 0; i < territoryNumber; i++){
//            if (!visited[i]) return false;
//        }
//    }
//    return true;
//}


// Traverses a graph
//void Map::Traverse(int j, vector<bool> visited) {
//    visited[j] = true;
//    for (int v = 0; v < territoryNumber; v++) {
//        if (borders[j][v] && !visited[v]) {
//            Traverse(v, visited);
//        }
//    }
//}

// --------------------------------------------------------------------------------------------------------------
// MapLoader

// Default constructor
MapLoader::MapLoader():map() {}

// Copy constructor
MapLoader::MapLoader(const MapLoader& m): map(map)
{
    this->fileName = m.fileName;
    this->map = m.map;
}

// Param. constructor
MapLoader::MapLoader(string fileName, Map* map)
{
    this->fileName = fileName;
    this->map = map;
}

// Assignment operator
MapLoader& MapLoader::operator= (const MapLoader& mL)
{
    this->fileName = mL.fileName;
    return *this;
}

// Destructor
MapLoader::~MapLoader()
{
    delete map;
    map = nullptr;
}

// Accessor
string MapLoader::getFileName()
{
    return this->fileName;
}

Map* MapLoader::getMap()
{
    return this->map;
}

// Mutator
void MapLoader::setFileName(string fileName)
{
    this->fileName = fileName;
}

void MapLoader::setMap(Map* map)
{
    this->map = map;
}

// Validate File
bool MapLoader::read()
{
    std::ifstream in(fileName);
    bool valid = false;
    string line;
    int sectionsFound = 0;

    // Check if file contains countries (territories)
    while (getline(in, line)) {

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
                this->map->addContinent(lineSplit[0]);
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
                    line = line.substr(index + 1);
                }
                
                this->map->addTerritory(new Territory(stoi(lineSplit[0]), lineSplit[1], stoi(lineSplit[2]), stoi(lineSplit[3]), stoi(lineSplit[4]) , nullptr, 0));
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

                vector<int> lineSplit;
                string border = "";

                //putting borders inside of the vector lineSplit
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                    {
                        lineSplit.push_back(stoi(border));
                        border = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        border = border + line[i];
                        lineSplit.push_back(stoi(border));
                        border = "";
                    }
                    else {
                        border = border + line[i];
                    }
                }
                this->map->addBorder(lineSplit);
                cout << *map << endl;
            }
            sectionsFound++;
        }
        valid = (sectionsFound == 3);
    }
    in.close();

    // Exit if file is invalid
    if (!valid) {
        cout << "Invalid File";
        exit(0);
    }

    return valid;
}

// Stream assignment operator
std::ostream& operator<<(std::ostream& strm, const MapLoader& mL)
{
    return strm << "MapLoader(" << mL.fileName << ")";
}