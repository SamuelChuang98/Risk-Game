#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Map.h"

int mapSpace::mapMain()
{

    // Create Players
    Player* player1 = new Player("Alex");
    Player* player2 = new Player("Samuel");

    //------------------------------------------------------------------------------------
    // Territory class tests

    // Create territories
    Territory* NA_Territory1 = new Territory("Canada", "NA", player1, 10);
    Territory* NA_Territory2 = new Territory("USA", "NA", player2, 28);
    Territory* NA_Territory3 = new Territory("Mexico", "NA", player1, 7);

    cout << NA_Territory1->toString() << "\n";
    cout << NA_Territory2->toString() << "\n";
    cout << NA_Territory3->toString() << "\n";

    //------------------------------------------------------------------------------------
    // Map/MapLoader tests

    // Declare file
    string* fileName = new string("bigeurope/bigeurope.map");

    // Store file in MapLoader Object
    MapLoader* mL = new MapLoader(fileName);

    if(mL->read()) {
        mL->getTerritoriesFromFile();
    } else
        exit(0);

    return 0;
}