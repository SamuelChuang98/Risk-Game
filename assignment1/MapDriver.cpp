#include <iostream>
#include <string>
#include <vector>

#include "Map.h"

using namespace std;

// Tests
int mapSpace::mapMain() 
{
    Territory t = {"Canada", "NA", 6};
    cout << t.toString() + "\n";
    t.setTerritoryName("France");
    t.setContinent("EU");
    t.setNumberOfArmies(9);
    cout << t.toString();
}