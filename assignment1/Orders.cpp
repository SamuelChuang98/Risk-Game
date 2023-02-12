#include "Orders.h"

using std::cout;
using std::endl;

Order::Order(){}
Order::~Order(){}

//This validates the order
void Order::validate()
{
    cout << "Validating order..." << endl;
    valid = true;
}

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
}

Deploy::~Deploy(){}

string* Deploy::get_type()
{
    return &type1;
}

Advance::Advance()
{
    set_id(1);
}

Advance::~Advance(){}

Bomb::Bomb()
{
    set_id(2);
}

Bomb::~Bomb(){}

Blockade::Blockade()
{
    set_id(3);
}

Blockade::~Blockade(){}

Airlift::Airlift()
{
    set_id(4);
}

Airlift::~Airlift(){}

Negotiate::Negotiate()
{
    set_id(5);
}

Negotiate::~Negotiate(){}