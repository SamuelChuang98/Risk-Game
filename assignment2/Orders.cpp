#include "Orders.h"
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

using std::cout;
using std::endl;

Order::Order(){}
Order::~Order(){}

//This validates the order
/*void Order::validate()
{
	cout << "Validating order..." << endl;
	valid = true;
}*/

//This executes the order
void Order::execute()
{
    if (valid) {
        cout << "Executing order..." << endl;
    }
}

//This sets the type id
void Order::set_id(int num)
{
    type_id = num;
}

//This returns the type of the Order
string Order::get_type()
{
    return vec_type1.at(type_id);
}

//This function adds an order to the Order List
void OrderList::set_order_list(Order* anOrder)
{
    vec_order_list.push_back(anOrder);
}

//This returns the order list
vector<Order*>* OrderList::get_order_list()
{
    return &vec_order_list;
}

//This deletes an order
void OrderList::delete_order(Order* delOrder)
{
    for (int i = 0; i < vec_order_list.size(); i++) {
        if (delOrder->get_type() == vec_order_list.at(i)->get_type()) {
            vec_order_list.erase(vec_order_list.begin() + i);

            return;
        }
    }
}

//This moves a position from its current to a new position
void OrderList::move(int position, int newPosition)
{

    int listSize = vec_order_list.size();

    if (position >= 0 && position < listSize && newPosition >= 0 && newPosition < listSize )
    {
        Order* temp = vec_order_list[position];
        vec_order_list.erase(vec_order_list.begin() + position);
        vec_order_list.insert(vec_order_list.begin() + newPosition, temp);
    }
    else {
        cout << "\nInvalid position." << endl;
    }
}

Deploy::Deploy()
{
    set_id(0);

    target = nullptr;
    amount = nullptr;

    execute();
}

Deploy::~Deploy(){}

string* Deploy::get_type()
{
    return &type1;
}

Advance::Advance()
{
    set_id(1);
    validate();
    execute();
}

Advance::~Advance(){}

Bomb::Bomb()
{
    set_id(2);
    validate();
    execute();
}

Bomb::~Bomb(){}

Blockade::Blockade()
{
    set_id(3);
    validate();
    execute();
}

Blockade::~Blockade(){}

Airlift::Airlift()
{
    set_id(4);
    validate();
    execute();
}

Airlift::~Airlift(){}

Negotiate::Negotiate()
{
    set_id(5);
    validate();
    execute();
}

Negotiate::~Negotiate(){}

// =============================== Validate of each order begins here =======================

bool Deploy::validate() const
{
    cout << "Validating Deploy...\n";

    if (target->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "You do not own this territory!\n" << endl;
        return false;
    }

    else if (*amount > currentPlayer->getReinforcementPool())
    {
        cout << "You do not have this many armies in the reinforcement pool!\n" << endl;
        return false;
    }

    else if (*amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

bool Advance::validate() const
{
    cout << "Validating Advance...\n";

    if (source->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "The source territory is not your own!\n" << endl;
        return false;
    }

    else if (!source->isAdjacent(target))
    {
        cout << "The target territory is not adjacent to the source territory!\n" << endl;
        return false;
    }

    else if (*amount > source->getNumOfArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
        return false;
    }

    else if (*amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

bool Bomb::validate() const
{
    cout << "Validating Bomb...\n";

    if(target->getTerritoryPlayerID() == currentPlayer->getPlayerID())
    {
        cout << "This territory is your own!\n" << endl;
        return false;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

bool Blockade::validate() const
{
    cout << "Validating Blockade...\n";

    if(target->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "This is not your territory! This order can only be played on your own territory!\n" << endl;
        return false;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

bool Airlift::validate() const
{
    cout << "Validating Airlift...\n";

    if (source->getTerritoryPlayerID() != currentPlayer->getPlayerID())
    {
        cout << "The source territory is not your own!\n" << endl;
        return false;
    }

    else if (*amount > source->getNumOfArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
    }

    else if (*amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

bool Negotiate::validate() const
{
    cout << "Validating Negotiate...\n";

    if(targetPlayer->getPlayerID() == currentPlayer->getPlayerID())
    {
        cout << "You cannot negotiate with yourself!\n" << endl;
        return false;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}