#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



using namespace std;

class Player;
class Territory;


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

    bool validate() const;
    void execute() const;

private:
    string type1 = { "deploy" };
    //bool validate() const;
    Territory *target;
};

class Advance : public Order {
public:
    Advance();
    ~Advance();

private:
    bool validate() const;
};

class Bomb : public Order
{
public:
    Bomb();
    ~Bomb();

private:
    bool validate() const;
};

class Blockade : public Order
{
public:
    Blockade();
    ~Blockade();
private:
    bool validate() const;
};

class Airlift : public Order
{
public:
    Airlift();
    ~Airlift();
private:
    bool validate() const;
};

class Negotiate : public Order
{
public:
    Negotiate();
    ~Negotiate();

private:
    bool validate() const;
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