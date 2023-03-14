//#include <iostream>

#include "Player.h"

//using namespace std;
int playerSpace::playerMain() 
{
    // Create territories for p1 and p2
    vector<Territory*> p1Ters = { new Territory("Quebec", "NA", 3), new Territory("Ontario", "NA", 0),
        new Territory("Alberta", "NA", 2) };
    vector<Territory*> p2Ters = { new Territory("Minnesota", "NA", 4), new Territory("Wisconsin", "NA", 1),
        new Territory("Michigan", "NA", 3) };
    
    // Create hands of cards for p1 and p2
    Deck* deck = new Deck;
    Hand* p1Hand = new Hand;
    p1Hand->addToHand(deck->draw());
    p1Hand->addToHand(deck->draw());
    Hand *p2Hand = new Hand;
    p2Hand->addToHand(deck->draw());
    p2Hand->addToHand(deck->draw());

    // Create order lists for p1 and p2
    OrderList* p1Orders = new OrderList();
    OrderList* p2Orders = new OrderList();

    // Initialize p1 and p2 with earlier created vectors.
    Player p1 = {p1Ters, p1Hand, p1Orders};
    Player p2 = {p2Ters, p2Hand, p2Orders};


    // Print players' arbitrary lists of territories to be defended and attacked are printed.

    vector<Territory*> p1ToAttack = p1.toAttack();
    cout << "\nTerritories for " << p1 << " to attack : ";
    for (Territory *ter: p1ToAttack) {
        cout << ter->getTerritoryName() << " ";
    }

    vector<Territory*> p1ToDefend = p1.toDefend();
    cout << endl << "Territories for " << p1 << " to defend : ";
    for (Territory *ter: p1ToDefend) {
        cout << ter->getTerritoryName() << " ";
    }

    vector<Territory*> p2ToAttack = p2.toAttack();
    cout << endl << "Territories for " << p2 << " to attack : ";
    for (Territory *ter: p2ToAttack) {
        cout << ter->getTerritoryName() << " ";
    }

    vector<Territory*> p2ToDefend = p2.toDefend();
    cout << endl << "Territories for " << p2 << " to defend : ";
    for (Territory *ter: p2ToDefend) {
        cout << ter->getTerritoryName() << " ";
    }

    // Testing issueOrder() on p1
    
    cout << endl << "\nQuantity of orders in p1 before issueOrder(): " 
        << p1.getOrders()->get_order_list()->size() << endl;

    p1.issueOrder();

    cout << "Quantity of orders in p1 after issueOrder(): "
        << p1.getOrders()->get_order_list()->size() << endl;

    // Print contents of each players' hand as well as stream insertion operator

    cout << endl << p1 << " has cards : " << endl;
    p1.getHand()->printHand();

    cout << p2 << " has cards : " << endl;
    p2.getHand()->printHand();

    // Delete contents of pointers

    for (Territory *t: p1Ters) {
        delete t;
    }
    p1Ters.clear();

    for (Territory* t : p2Ters) {
        delete t;
    }
    p1Ters.clear();

    delete p1Hand;
    p1Hand = NULL;
    delete p2Hand;
    p2Hand = NULL;
    delete deck;
    deck = NULL;

    delete p1Orders;
    p1Orders = NULL;
    delete p2Orders;
    p2Orders = NULL;

    return 0;
}
