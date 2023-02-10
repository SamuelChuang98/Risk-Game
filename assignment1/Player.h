
#pragma once

#include <vector>
#include <iostream>
#include "Cards.h"

using namespace std;
namespace playerSpace{
    int playerMain();
}

class Player {
    // TODO: Replace strings with their respective types

public:
    Player();

    Player(vector<string *> ters, Hand *hand/* vector<string *> cards*/, vector<string *> orders);

    Player(Player &p);

    ~Player();

    Player &operator=(const Player &rightSide);    // Assignment operator
    vector<string *> toDefend();    // Type will be Territory*
    vector<string *> toAttack();    // Type will be Territory*
    Hand *hand;                      //User has a hand of cards
    void issueOrder();

private:
    vector<string *> ters;        // Type will be Territory*
    //vector<string *> hands;        // Type will be hands*
    vector<string *> orders;        // Type will be Orders*
    friend std::ostream &operator<<(std::ostream &strm, const Player &p);
};

