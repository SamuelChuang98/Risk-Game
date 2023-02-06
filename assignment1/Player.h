#include <vector>

#pragma once

using namespace std;

class Player
{
	// TODO: Replace strings with their respective types

	public:
		Player();
		Player(vector<string*> ters, vector<string*> cards, vector<string*> orders);
		Player(Player &p);
		~Player();
		Player& operator = (const Player& rightSide);	// Assignment operator
		vector<string*> toDefend();	// Type will be Territory*
		vector<string*> toAttack();	// Type will be Territory*
		void issueOrder();

	private:
		vector<string*> ters;		// Type will be Territory*
		vector<string*> cards;		// Type will be Cards*
		vector<string*> orders;		// Type will be Orders*
		friend std::ostream& operator<<(std::ostream &strm, const Player &p);
};
