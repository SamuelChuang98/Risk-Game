
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
    Player(vector<Territory*> ters, Hand* hand, OrderList* orders);
    Player(Player &p);
    ~Player();
    Player &operator=(const Player &rightSide);    // Assignment operator
    Hand* getHand();
    OrderList* getOrders();
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder();

private:
    vector<Territory*> ters;    // Vector of territories owned by the player
    Hand* hand;                 // Hand of cards owned by the player
    OrderList* orders;          // List of orders owned by the player
    friend std::ostream &operator<<(std::ostream &strm, const Player &p);
};

