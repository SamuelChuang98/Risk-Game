//#include <iostream>

#include "Player.h"

//using namespace std;
int playerSpace::playerMain() {
    // Create vectors of strings that will represent territories, cards, and orders of p1 and p2.
    vector<string *> p1Ters = {new string("Quebec"), new string("Ontario"), new string("Alberta")};
   // vector<string *> p1Cards = {new string("Bomb1"), new string("Airlift2")};
    Deck *deck = new Deck;
    Hand * p1Cards = new Hand;
    p1Cards->addToHand(deck->draw());
    p1Cards->addToHand(deck->draw());
    vector<string *> p1Orders = {new string("Deploy to Quebec"), new string("Attack Vermont")};

    vector<string *> p2Ters = {new string("Minnesota"), new string("Wisconsin"), new string("Michigan")};
   // vector<string *> p2Cards = {new string("Airlift3"), new string("Blockade2")};
    Hand *p2Cards = new Hand;
    p2Cards->addToHand(deck->draw());
    p2Cards->addToHand(deck->draw());

    vector<string *> p2Orders = {new string("Deploy to Wisconsin"), new string("Attack Iowa")};

    // Initialize p1 and p2 with earlier created vectors.
    Player p1 = {p1Ters, p1Cards, p1Orders};
    Player p2 = {p2Ters, p2Cards, p2Orders};


    // Players' arbitrary lists of territories to be defended and attacked are printed.

    vector<string *> p1ToAttack = p1.toAttack();
    cout << "Territories for " << p1 << " to attack : ";
    for (string *ter: p1ToAttack) {
        cout << *ter << " ";
    }

    vector<string *> p1ToDefend = p1.toDefend();
    cout << endl << "Territories for " << p1 << " to defend : ";
    for (string *ter: p1ToDefend) {
        cout << *ter << " ";
    }

    vector<string *> p2ToAttack = p2.toAttack();
    cout << endl << "Territories for " << p2 << " to attack : ";
    for (string *ter: p2ToAttack) {
        cout << *ter << " ";
    }

    vector<string *> p2ToDefend = p2.toDefend();
    cout << endl << "Territories for " << p2 << " to defend : ";
    for (string *ter: p2ToDefend) {
        cout << *ter << " ";
    }

    cout << endl << p1 << " Has cards : " << endl;
    p1.hand->printHand();

    cout << endl << p2 << " Has cards : " << endl;
    p2.hand->printHand();

    cout << endl <<  " Current deck status : " << endl ;
    deck->printDeck();

    // Delete contents of pointers

    for (string *s: p1Ters) {
        delete s;
    }
    p1Ters.clear();

    /*for (string *s: p1Cards) {
        delete s;
    }
    p1Cards.clear();*/

    delete p1Cards;
    p1Cards = NULL;

    for (string *s: p1Orders) {
        delete s;
    }
    p1Orders.clear();

    for (string *s: p2Ters) {
        delete s;
    }
    p2Ters.clear();

    /*for (string *s: p2Cards) {
        delete s;
    }
    p2Cards.clear();*/

    delete p2Cards;
    p2Cards = NULL;

    for (string *s: p2Orders) {
        delete s;
    }
    p2Orders.clear();

    delete deck;
    deck = NULL;

    return 0;
}
