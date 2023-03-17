
#pragma once

#include <vector>
#include <iostream>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;
namespace playerSpace{
    int playerMain();
}

class Player {
    // TODO: Replace strings with their respective types

public:
    Player();
    Player(vector<Territory*> ters, Hand* hand,OrderList* orders, int reinforcementPool);
    Player(Player &p);
    ~Player();
    Player &operator=(const Player &rightSide);    // Assignment operator
    // Hand* getHand();
    // OrderList* getOrders();
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder();


    // Accessors
    vector<Territory*> getTerritories();
    Hand* getHand();
    OrderList* getOrders();
    int getReinforcementPool();

    // Mutators
    void setTerritories(vector<Territory*> ters);
    void setHand(Hand* hand);
    void setOrders(OrderList* orders);
    void setReinforcementPool(int reinforcement);

private:
    vector<Territory*> ters;    // Vector of territories owned by the player
    Hand* hand;                 // Hand of cards owned by the player
    OrderList* orders;          // List of orders owned by the player
    int reinforcementPool;      // Reinforcement allocated to a player
    friend std::ostream &operator<<(std::ostream &strm, const Player &p); // stream insertion operator
};

