
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

public:
    Player();
    Player(int pID, vector<Territory*> ters, Hand* hand,OrderList* orders, int reinforcementPool, bool hasContinentBonus);
    Player(Player &p);
    ~Player();
    Player &operator=(const Player &rightSide);    // Assignment operator
    // Hand* getHand();
    // OrderList* getOrders();
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(vector<Territory*> t);
    void addFriendly(Player &p);

    bool ContinentBonus(vector<Territory*> continent); // get continent bonus value

    // Accessors
    int getPiD();
    vector<Territory*> getTerritories();
    Hand* getHand();
    OrderList* getOrders();
    int getReinforcementPool();
    vector<Player*> getFriendlies();
    bool getContinentBonus();

    // Mutators
    void setPiD(int pID);
    void setTerritories(vector<Territory*> ters);
    void setHand(Hand* hand);
    void setOrders(OrderList* orders);
    void setReinforcementPool(int reinforcement);
    void setContinentBonus(bool CB);

private:
    int pID; // player ID
    vector<Territory*> ters;    // Vector of territories owned by the player
    Hand* hand;                 // Hand of cards owned by the player
    OrderList* orders;          // List of orders owned by the player
    int reinforcementPool;      // Reinforcement allocated to a player
    friend std::ostream &operator<<(std::ostream &strm, const Player &p); // stream insertion operator
    vector<Player*> friendlies; // Vector of allies of the player
    bool hasContinentBonus; // continent bonus
};

