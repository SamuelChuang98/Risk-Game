#include "Map.h"

int mapSpace::mapMain()
{

    // Create Players
    TemporaryPlayer* player1 = new TemporaryPlayer("player 1");
    TemporaryPlayer* player2 = new TemporaryPlayer("player 2");

    //------------------------------------------------------------------------------------
    // Territory class tests

    // Create territories
    Territory* t1 = new Territory(1,"Canada", 5,30,353, player1, 10);
    Territory* t2 = new Territory(2, "Lebanon", 4, 233, 64, player2, 1);
    Territory* t3 = new Territory(3, "Mars", 2, 31, 312, player1, 3);
    //------------------------------------------------------------------------------------
    // Map/MapLoader tests
    
    Map* map = new Map();

    // Declare file
    string fileName = "C:\\Users\\aitan\\Documents\\visual studio workspace\\A2\\germany2.map";
    // Store file in MapLoader Object
    MapLoader mapLoader = MapLoader(fileName, map);

    mapLoader.read();


    return 0;
}

int main() {
    mapSpace::mapMain();
}