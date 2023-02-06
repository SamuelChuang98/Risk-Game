#include <iostream>
#include <vector>

#include "Player.h"

// Default constructor
Player::Player()
{

}

// Param. constructor
Player::Player(vector<string*> ters, vector<string*> cards, vector<string*> orders)
{
	for (string* ter : ters) {
		this->ters.push_back(new string(*ter));
	}

	for (string* card : cards) {
		this->cards.push_back(new string(*card));
	}

	for (string* order : orders) {
		this->orders.push_back(new string(*order));
	}
}

// Copy constructor - performs deep copy
Player::Player(Player& p)
{
	for (string* ter : p.ters) {
		this->ters.push_back(new string(*ter));
	}

	for (string* card : p.cards) {
		this->cards.push_back(new string(*card));
	}

	for (string* order : p.orders) {
		this->orders.push_back(new string(*order));
	}
}


// Destructor
Player::~Player() 
{
	// Delete dynamically allocated strings pointed to in ters vector
	for (string* ter : ters) {
		delete ter;
	}
	ters.clear();	// Remove pointers from ters

	for (string* card : cards) {
		delete card;
	}
	cards.clear();

	for (string* order : orders) {
		delete order;
	}
	orders.clear();
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
	string* order = new string();	// Type will be Order*
	orders.push_back(order);
}


