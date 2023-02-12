#pragma once 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

namespace orderSpace{
    int orderMain();
}
class Order
{
public :
	Order();
	~Order();
	//Order(const Order& O);//copy constructor
	//Order& operator = (const Order &O);//assignment construtor
	

	//check of the order is valid 
	void validate();
	//execute method 
	void execute();
	
	//set type of the subclass
	void set_type_id(int num);
	string get_type();

private :
	bool valid;
	vector<string> vec_type1 = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
	int type_id;
};


//Note that the orders’ actions do not need to be implemented at this point.


class Deploy : public Order 
{

public:
	Deploy();
	~Deploy();
	string* get_type();
private:
	string type1 = { "deploy" };
};

class Advance : public Order {
public:
	Advance();
	~Advance();

private:
};

class Bomb : public Order 
{
public:
	Bomb();
	~Bomb();

private:
};

class Blockade : public Order
{
public:
	Blockade();
	~Blockade();
private:
};

class Airlift : public Order
{
public:
	Airlift();
	~Airlift();
private:
};

class Negotiate : public Order
{
public:
	Negotiate();
	~Negotiate();

private:
};

class OrderList
{
public:
	void set_order_list(Order* an_order);
	vector<Order*>* get_order_list();
	//delete an order
	void delete_order(Order* oneOrder);
	//move
	void move(int position, int new_position);

private:
	vector<Order*> vec_order_list; //store the orders
};