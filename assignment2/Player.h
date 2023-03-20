
#pragma once

#include <vector>
#include <iostream>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;



namespace playerSpace {
    int playerMain();
}

class Player {

public:
    Player();
    Player(int pID, vector<Territory*> ters, Hand* hand, OrderList* orders, int reinforcementPool);
    Player(Player& p);
    ~Player();
    Player& operator=(const Player& rightSide);    // Assignment operator
    // Hand* getHand();
    // OrderList* getOrders();
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder();
    void addFriendly(Player& p);
    void addPlayerTerritory(Territory* t);


    // Accessors
    int getPlayerID();
    vector<Territory*> getTerritories();
    Hand* getHand();
    OrderList* getOrders();
    int getReinforcementPool();
    vector<Player*> getFriendlies();
    string getPlayerName();
    int getPiD();

    // Mutators
    void setPlayerID(int id);
    void setTerritories(vector<Territory*> ters);
    void setHand(Hand* hand);
    void setOrders(OrderList* orders);
    void setReinforcementPool(int reinforcement);
    void setPlayerName(string playerName);
    void setPiD(int pID);

private:
    int playerID;
    int pID;
    string playerName;
    vector<Territory*> ters;    // Vector of territories owned by the player
    Hand* hand;                 // Hand of cards owned by the player
    OrderList* orders;          // List of orders owned by the player
    int reinforcementPool;      // Reinforcement allocated to a player
    friend std::ostream& operator<<(std::ostream& strm, const Player& p); // stream insertion operator
    vector<Player*> friendlies; // Vector of allies of the player
};
