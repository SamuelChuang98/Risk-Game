#pragma once 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

namespace orderSpace{
    int orderMain();
}
class Order
{
public :
	Order();
	~Order();
	
	void validate();
	void execute();

	void set_id(int num);
	string get_type();

private :
	bool valid;
	vector<string> vec_type1 = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
	int type_id;
};

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

	void delete_order(Order* oneOrder);
	void move(int position, int new_position);

private:
	vector<Order*> vec_order_list; //store the orders
};