#include <iostream>

#include "Player.h"

using namespace std;

int main()
{


	// Create vectors of strings that will represent territories, cards, and orders of p1 and p2.
	vector<string*> p1Ters = {new string("Quebec"), new string("Ontario"), new string("Alberta")};
	Hand* p1Cards = new Hand();
	OrderList* p1Orders = new OrderList();


	vector<string*> p2Ters = { new string("Minnesota"), new string("Wisconsin"), new string("Michigan") };
	Hand* p2Cards = new Hand();
	OrderList* p2Orders = new OrderList();

	// Initialize p1 and p2 with earlier created vectors.
	Player p1 = {p1Ters, p1Cards, p1Orders};
	Player p2 = {p2Ters, p2Cards, p2Orders};


	// Players' arbitrary lists of territories to be defended and attacked are printed.

	vector<string*> p1ToAttack = p1.toAttack();
	cout << "Territories for " << p1 << " to attack : ";
	for (string* ter : p1ToAttack) 
	{
		cout << *ter << " ";
	}

	vector<string*> p1ToDefend = p1.toDefend();
	cout << endl << "Territories for " << p1 << " to defend : ";
	for (string* ter : p1ToDefend)
	{
		cout << *ter << " ";
	}

	vector<string*> p2ToAttack = p2.toAttack();
	cout << endl << "Territories for " << p2 << " to attack : ";
	for (string* ter : p2ToAttack)
	{
		cout << *ter << " ";
	}

	vector<string*> p2ToDefend = p2.toDefend();
	cout << endl << "Territories for " << p2 << " to defend : ";
	for (string* ter : p2ToDefend)
	{
		cout << *ter << " ";
	}

	// Issue order for each player
	p1.issueOrder();
	p2.issueOrder();
	cout << endl << "New orders issued." << endl;

	// Delete contents of pointers
	
	for (string* s : p1Ters) {
		delete s;
	}
	p1Ters.clear();

	delete p1Cards;
	delete p1Orders;

	for (string* s : p2Ters) {
		delete s;
	}
	p2Ters.clear();

	delete p2Cards; 
	delete p2Orders;

}
