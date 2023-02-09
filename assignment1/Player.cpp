#include <iostream>
#include <vector>

#include "Player.h"

// Default constructor
Player::Player()
{
	cards = new Hand();
	orders = new OrderList();
}

// Param. constructor
Player::Player(vector<string*> ters, Hand* cards, OrderList* orders)
{
	for (string* ter : ters) {
		this->ters.push_back(new string(*ter));
	}

	// TODO: Uncomment; No copy constructor/assignment op yet 
	// this->cards = new Hand(cards);
	this->cards = new Hand();

	// TODO: Uncomment; No copy constructor/assignment op yet 
	// this->orders = new Order(orders);
	this->orders = new OrderList();
	
}

// Copy constructor - performs deep copy
Player::Player(Player& p)
{
	for (string* ter : p.ters) {
		this->ters.push_back(new string(*ter));
	}

	// TODO: Uncomment; No copy constructor/assignment op yet 
	// this->cards = new Hand(p.cards);
	this->cards = new Hand();

	// TODO: Uncomment; No copy constructor/assignment op yet 
	// orders = new OrderList(p.orders);
	orders = new OrderList();
}


// Destructor
Player::~Player() 
{
	// Delete dynamically allocated strings pointed to in ters vector
	for (string* ter : ters) {
		delete ter;
	}
	ters.clear();	// Remove pointers from ters

	delete cards;
	delete orders;
}

// Assignment operator - performs shallow copy
Player& Player::operator=(const Player& rightSide)
{
	this->ters = rightSide.ters;
	this->cards = rightSide.cards;
	this->orders = rightSide.orders;
	return *this;
}

// Stream insertion operator, returns player's first territory as a stream
std::ostream& operator<<(std::ostream &strm, const Player& p)
{
	return strm << "Player(" << *p.ters.at(0) << ")";
}


vector<string*> Player::toDefend()
{
	vector<string*> defenseTers;

	// Return half the territories from this player for now.
	for (int i = 0; i < ters.size(); i = i + 2) {
		defenseTers.push_back(ters.at(i));
	}

	return defenseTers;
}

vector<string*> Player::toAttack()
{
	vector<string*> attackTers;

	// Return the other half of territories from this player for now.
	for (int i = 1; i < ters.size(); i = i + 2) {
		attackTers.push_back(ters.at(i));
	}

	return attackTers;
}

void Player::issueOrder()
{
	Order* order = new Order();
	orders->set_order_list(order);
}


