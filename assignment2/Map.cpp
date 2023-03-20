#include "Map.h"

using namespace std;

// --------------------------------------------------------------------------------------------------------------
// Continent

Continent::Continent() {
    this->continentName = "";
    this->armyNumber = 0;
    this->color = "";
}

Continent::Continent(string continentName, int armyNumber, string color) {
    this->continentName = continentName;
    this->armyNumber = armyNumber;
    this->color = color;
}

Continent::~Continent(){}

string Continent::getContinentName() { return this->continentName; }
int Continent::getArmyNumber() { return this->armyNumber; }
string Continent::getColor() { return this->color; }

void Continent::setContinentName(string continentName) { this->continentName = continentName; }
void Continent::setArmyNumber(int armyNumber) { this->armyNumber = armyNumber; }
void Continent::setColor(string color) { this->color = color; }

std::ostream& operator<<(std::ostream& os, const Continent& c) {
    return os << "Name: " << c.continentName << "\tArmy Number: " << c.armyNumber << "\tColor: " << c.color;
}


// --------------------------------------------------------------------------------------------------------------
// Territory

// Default constructor
Territory::Territory() {
    this->territoryNumber = 0;
    this->territoryName = "";
    this->continent = 0;
    this->x = 0;
    this->y = 0;
    this->numberOfArmies = 0;
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
Territory::Territory(int territoryNumber, string territoryName, int continent, int x, int y, Player* player, int numberOfArmies)
{
    this->territoryNumber = territoryNumber;
    this->territoryName = territoryName;
    this->continent = continent;
    this->x = x;
    this->y = y;
    this->player = player;
    this->numberOfArmies = numberOfArmies;
}

// Parameterized constructor
//Territory::Territory(int territoryNumber, string territoryName, int continent, int x, int y, int numberOfArmies)
//{
//    this->territoryNumber = territoryNumber;
//    this->territoryName = territoryName;
//    this->continent = continent;
//    this->x = x;
//    this->y = y;
//    this->numberOfArmies = numberOfArmies;
//}

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

bool Territory::isAdjacent(Territory& territory){
    return true;
}



// Territory stream insertion operator
std::ostream& operator<<(ostream& os, const Territory& t) {
    return os << "Number: " << t.territoryNumber << "\tName: " << t.territoryName << "\tContinent: " << t.continent << "\tx: " << t.x << "\ty: " << t.y  << "\tPlayer ID: " << t.player->getPlayerID() << "\tNumber of armies: " << t.numberOfArmies << endl;
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
Player* Territory::getPlayer() { return player; }
int Territory::getNumberOfArmies() { return numberOfArmies; }

// Territory mutators
void Territory::setTerritoryNumber(int newNumber) { this->territoryNumber = newNumber; }
void Territory::setTerritoryName(string newTerritoryName) { this->territoryName = newTerritoryName; }
void Territory::setContinent(int newContinent) { this->continent = newContinent; }
void Territory::setX(int x) { this->x = x; }
void Territory::setY(int y) { this->y = y; }
void Territory::setPlayer(Player* newPlayerName) { this->player = newPlayerName; }
void Territory::setNumberOfArmies(int newArmyCount) { this->numberOfArmies = newArmyCount; }

// --------------------------------------------------------------------------------------------------------------
// Map 

// Default constructor 
Map::Map() 
{ 
    
}

// Copy constructor
Map::Map(const Map& m) {
    this->continents = m.continents;
    this->borders = m.borders;
    this->territories = m.territories;
}


// Parameterized constructor
Map::Map(vector<Continent*> continents, vector<Territory*> territories, vector<vector<int>> borders){
    this->continents = continents;
    this->borders = borders;
    this->territories = territories;
}

//Accessors
vector<Continent*> Map::getContinents() { return this->continents; }
vector<vector<int>> Map::getBorders() { return this->borders; }
vector<Territory*> Map::getTerritories() { return this->territories; }

//Mutators
void Map::setContinents(vector<Continent*> continents) { this->continents = continents; }
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

    return strm << "Continents: " << m.continents.size() << "\tBorders: " << bordersNum << "\tTerritories: " << m.territories.size();
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

void Map::addContinent(Continent* continent)
{
    this->continents.push_back(continent);
}

void Map::addTerritory(Territory* territory)
{
    this->territories.push_back(territory);
}


// Validates Map
bool Map::Validate(){

    // check if countries are connected
    for (int i = 0; i < borders.size(); i++)
    {
        if (borders[i].size() < 2)
        {
            cout << "countries are not connected" << endl;
            return false;
        }
    }
    return true;
}

    //vector<bool> validate;
    //int currentBorderIndex = 0;
    //for (int i = 0; i < this->borders.size();i++)
    //{
    //    for (int j = 1; j < this->borders[i].size(); j++)
    //    {
    //        currentBorderIndex = this->borders[i][j] - 1;
    //        vector<int> temp;
    //        for (int k = 1; k < this->borders[currentBorderIndex].size(); k++)
    //        {
    //            if (borders[currentBorderIndex][k] == this->borders[i][0])
    //            {
    //                break;
    //            }
    //            else if(k = this->borders[currentBorderIndex].size() - 1)
    //            {
    //                return false;
    //            }
    //            
    //        }            
    //    }
    //    cout << "checking for " << this->borders[i][0];
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
MapLoader::MapLoader() {}

// Copy constructor
MapLoader::MapLoader(const MapLoader& m)
{
    this->fileName = m.fileName;
}

// Param. constructor
MapLoader::MapLoader(string fileName)
{
    this->fileName = fileName;
}

// Assignment operator
MapLoader& MapLoader::operator= (const MapLoader& mL)
{
    this->fileName = mL.fileName;
    return *this;
}

// Destructor
MapLoader::~MapLoader() { }

// Accessor
string MapLoader::getFileName()
{
    return this->fileName;
}

// Mutator
void MapLoader::setFileName(string fileName)
{
    this->fileName = fileName;
}

void Map::mapLoad(string fileName)
{
    string line;
    ifstream in(fileName);

    // keep reading until end of file
    while (getline(in, line)) {
        // Assumes a valid file will have continents, countries, then borders.
        if (line.find("[continents]") != string::npos) {

            while (true) {
                getline(in, line);

                // Break out if at end of continents
                if (line == "") {
                    break;
                }

                vector<string> newContinent;
                string continent = "";

                //break values into newContinent
                for (int i = 0; i < line.size(); i++) 
                {
                    if (line[i] == ' ')
                    {
                        newContinent.push_back(continent);
                        continent = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        continent = continent + line[i];
                        newContinent.push_back(continent);
                        continent = "";
                    }
                    else {
                        continent = continent + line[i];
                    }
                } 
                this->addContinent(new Continent(newContinent[0], stoi(newContinent[1]), newContinent[2]));
            }
        }
        else if (line.find("[countries]") != string::npos) {

            while (true) {
                getline(in, line);

                // Break out if at end of countries
                if (line == "") {
                    break;
                }

                vector<string> newCountry;
                string country = "";

                //break values into countriesChecker
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                    {
                        newCountry.push_back(country);
                        country = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        country = country + line[i];
                        newCountry.push_back(country);
                        country = "";
                    }
                    else {
                        country = country + line[i];
                    }
                }
                // add territory to map
                this->addTerritory(new Territory(stoi(newCountry[0]), newCountry[1], stoi(newCountry[2]), stoi(newCountry[3]), stoi(newCountry[4]), nullptr, 0));
            }
        }
        else if (line.find("[borders]") != string::npos) {

            while (true) {
                //read current line
                getline(in, line);

                // Break out if at end of borders
                if (line == "") {
                    break;
                }

                vector<string> newBorder;
                string border = "";

                //break values into newBorder
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                    {
                        newBorder.push_back(border);
                        border = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        border = border + line[i];
                        newBorder.push_back(border);
                        border = "";
                    }
                    else {
                        border = border + line[i];
                    }
                }

                vector<int> borderVec;
                for (int i = 0; i < newBorder.size(); i++)
                {
                    borderVec.push_back(stoi(newBorder[i]));
                }
                // add border to map
                this->addBorder(borderVec);
            }
        }
    }
    in.close();
    cout << *this << endl;
}

// Check if file is Valid
bool MapLoader::fileChecker()
{
    bool valid = false;
    string line;
    int sectionsFound = 0;
    std::ifstream in;

    size_t dot_pos = fileName.find_last_of(".");
    
    if (dot_pos == string::npos)
    {
        return false;
    }
    else if (dot_pos != string::npos)
    {
        string fileExtension = fileName.substr(dot_pos + 1);
        if (fileExtension != "map") { return false; }
    }

    in.open(fileName);
    //check if file exists in directory
    if (in.fail())
    {
        cout << "file not found" << endl;
        return false;
    }

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

                vector<string> continentsChecker; // name, army value, color
                string checker = "";

                //break values into continentsChecker
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                    {
                        continentsChecker.push_back(checker);
                        checker = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        checker = checker + line[i];
                        continentsChecker.push_back(checker);
                        checker = "";
                    }
                    else {
                        checker = checker + line[i];
                    }
                }
                //check if data members number is correct
                if (continentsChecker.size() != 3) 
                {
                    cout << "file does not match continent data members" << endl;
                    return false;
                }
                //check if a data memeber is empty
                for (int i = 0; i < 3; i++)
                {
                    if (continentsChecker[i] == "" || continentsChecker[i] == " ") 
                    { 
                        cout << "file does not match continent data members" << endl;
                        return false; 
                    }
                }
                //check if armyNumber is int
                try {
                    int i = stoi(continentsChecker[1]);
                }
                catch (exception e) {
                    cout << "file does not match continent data members" << endl;
                    return false;
                }
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

                vector<string> countriesChecker; // num, name, continent, x, y
                string checker = "";

                //break values into countriesChecker
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                    {
                        countriesChecker.push_back(checker);
                        checker = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        checker = checker + line[i];
                        countriesChecker.push_back(checker);
                        checker = "";
                    }
                    else {
                        checker = checker + line[i];
                    }
                }
                //check if data members number is correct
                if (countriesChecker.size() != 5)
                {
                    cout << "file does not match countries data members" << endl;
                    return false;
                }
                //check if a data memeber is empty
                for (int i = 0; i < 5; i++)
                {
                    if (countriesChecker[i] == "" || countriesChecker[i] == " ")
                    {
                        cout << "file does not match countries data members" << endl;
                        return false;
                    }
                }
                //check if TerritoryNum, armies, x, y are int
                try {
                    int i = stoi(countriesChecker[0]);
                    int j = stoi(countriesChecker[2]);
                    int k = stoi(countriesChecker[3]);
                    int l = stoi(countriesChecker[4]);
                }
                catch (exception e) {
                    cout << "file does not match countries data members" << endl;
                    return false;
                }
            }
            sectionsFound++;
        }
        else if (line.find("[borders]") != string::npos) {

            while (true) {
                //read current line
                getline(in, line);

                // Break out if at end of borders
                if (line == "") {
                    break;
                }

                vector<string> bordersChecker;
                string checker = "";

                //break values into bordersChecker
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == ' ')
                    {
                        bordersChecker.push_back(checker);
                        checker = "";
                    }
                    else if (i == line.size() - 1)
                    {
                        checker = checker + line[i];
                        bordersChecker.push_back(checker);
                        checker = "";
                    }
                    else {
                        checker = checker + line[i];
                    }
                }
                //check if a data memeber is empty
                for (int i = 0; i < bordersChecker.size(); i++)
                {
                    if (bordersChecker[i] == "" || bordersChecker[i] == " ")
                    {
                        cout << "invalid border" << endl;
                        return false;
                    }
                }
                //check if TerritoryNum, armies, x, y are int
                try {
                    for (int i = 0; i < bordersChecker.size(); i++)
                    {
                        int j = stoi(bordersChecker[i]);
                    }
                }
                catch (exception e) {
                    cout << "invalid border" << endl;
                    return false;
                }
            }
            sectionsFound++;
        }
        valid = (sectionsFound == 3);
    }
    in.close();

    return valid;
}

// Stream assignment operator
std::ostream& operator<<(std::ostream& strm, const MapLoader& mL)
{
    return strm << "File name: " << mL.fileName << endl;
}