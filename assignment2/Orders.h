#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Player;
class Order;
class Territory;

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

        bool validate();
        void execute();

        void set_id(int num);
        string get_type();

    protected:
        Player *thisPlayer;

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
    Deploy(const Deploy& other);

    string* get_type();

    bool validate() const;
    void execute() const;

protected:
    Player *currentPlayer;

private:
    string type1 = { "deploy" };
    //bool validate() const;
    Territory *target;
    int *amount;
};

class Advance : public Order {
public:
    Advance();
    ~Advance();
    Advance(const Advance& other);
private:
    bool validate() const;
    void execute() const;

    Territory *source;
    Territory *target;
    int *amount;
};

class Bomb : public Order
{
public:
    Bomb();
    ~Bomb();
    Bomb(const Bomb& other);
private:
    bool validate() const;
    void execute() const;

    Territory *target;
};

class Blockade : public Order
{
public:
    Blockade();
    ~Blockade();
    Blockade(const Blockade& other);
private:
    bool validate() const;
    void execute() const;

    Territory *target;
};

class Airlift : public Order
{
public:
    Airlift();
    ~Airlift();
    Airlift(const Airlift& other);
private:
    bool validate() const;
    void execute() const;

    Territory *source;
    Territory *target;
    int *amount;
};

class Negotiate : public Order
{
public:
    Negotiate();
    ~Negotiate();
    Negotiate(const Negotiate& other);
private:
    bool validate() const;
    void execute() const;

    Player *targetPlayer;

};

class OrderList
{
public:
    OrderList();
    OrderList(OrderList const &other);
    ~OrderList();

    void set_order_list(Order* an_order);
    vector<Order*>* get_order_list() const;

    void delete_order(Order* oneOrder);
    void move(int position, int new_position);
    void execute_orders();

private:
    vector<Order*> vec_order_list; //store the orders
    vector<Order *> *get_order_list();
};

void simulateAttack(Territory*, Territory*, Player*, int*);
