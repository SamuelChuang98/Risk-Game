#include <iostream>
#include <vector>

#include "Player.h"

// Default constructor
Player::Player()
{
    hand = new Hand();
    orders = new OrderList();
}

// Param. constructor
Player::Player(vector<Territory*> ters, Hand* hand, OrderList* orders) 
{
    for (Territory *ter: ters) {
        this->ters.push_back(new Territory(*ter));
    }

    this->hand = new Hand(*hand);

    this->orders = new OrderList();
}

// Copy constructor - performs deep copy
Player::Player(Player &p) 
{
    for (Territory *ter: p.ters) {
        this->ters.push_back(new Territory(*ter));
    }

   this->hand =  new Hand(*p.hand);

   orders = new OrderList(*p.orders);
}


// Destructor
Player::~Player() 
{
    // Delete dynamically allocated territories pointed to in ters vector
    for (Territory *ter: ters) {
        delete ter;
    }
    ters.clear();    // Remove pointers from ters

   /* for (string *hand: hands) {
        delete hand;
    }
    hands.clear();*/
    delete hand;
    hand = NULL;

    delete orders;
    orders = NULL;
}

// Assignment operator - performs shallow copy
Player &Player::operator=(const Player &rightSide) {
    this->ters = rightSide.ters;
    this->hand = rightSide.hand;
    this->orders = rightSide.orders;
    return *this;
}

Hand* Player::getHand()
{
    return hand;
}

OrderList* Player::getOrders()
{
    return orders;
}

// Stream insertion operator, returns player's first territory as a stream
std::ostream &operator<<(std::ostream &strm, const Player &p) {
    return strm << "Player(" << p.ters.at(0)->getTerritoryName() << ")";
}


vector<Territory*> Player::toDefend() {
    vector<Territory*> defenseTers;

    // Return half the territories from this player for now.
    for (int i = 0; i < ters.size(); i = i + 2) {
        defenseTers.push_back(ters.at(i));
    }

    return defenseTers;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> attackTers;

    // Return the other half of territories from this player for now.
    for (int i = 1; i < ters.size(); i = i + 2) {
        attackTers.push_back(ters.at(i));
    }

    return attackTers;
}

void Player::issueOrder() {
    Order* order = new Order();
    orders->set_order_list(order);
}


