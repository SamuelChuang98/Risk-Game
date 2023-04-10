#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Player.h"
#include "Subject.h"
#include "ILoggable.h"

class Player;
class Order;
class Territory;

using namespace std;

class Player;
class Territory;


namespace orderSpace{
    int orderMain();
}
class Order : public Subject, public ILoggable
{
    public :
        Order();
        ~Order();

        bool validate();
        void execute();

        void set_id(int num);
        string get_type();

        void StringTolog() override;
    protected:
        Player *thisPlayer;

    private :
        bool valid;
        vector<string> vec_type1 = { "deploy", "advance", "bomb", "blockade", "airlift", "negotiate" };
        int type_id;
        vector<Territory*> pTerritories;
};

class Deploy : public Order
{
public:
    Deploy();
    Deploy(Player* player, Territory* target, int* amount);
    ~Deploy();
    Deploy(const Deploy& other);

    string* get_type();

    bool validate() const;
    void execute();

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
    Advance(Player* player, Territory* source, Territory* target, int* amount);
    ~Advance();
    Advance(const Advance& other);
private:
    bool validate() const;
    void execute();

    Territory *source;
    Territory *target;
    int *amount;
};

class Bomb : public Order
{
public:
    Bomb();
    Bomb(Player* player, Territory* target);
    ~Bomb();
    Bomb(const Bomb& other);
private:
    bool validate() const;
    void execute();

    Territory *target;
};

class Blockade : public Order
{
public:
    Blockade();
    Blockade(Player* player, Territory* target);
    ~Blockade();
    Blockade(const Blockade& other);
private:
    bool validate() const;
    void execute();

    Territory *target;
};

class Airlift : public Order
{
public:
    Airlift();
    Airlift(Player* player, Territory* source, Territory* target, int* amount);
    ~Airlift();
    Airlift(const Airlift& other);
private:
    bool validate() const;
    void execute();

    Territory *source;
    Territory *target;
    int *amount;
};

class Negotiate : public Order
{
public:
    Negotiate();
    Negotiate(Player* player, Player* targetPlayer);
    ~Negotiate();
    Negotiate(const Negotiate& other);
private:
    bool validate() const;
    void execute();

    Player *targetPlayer;
    Territory *target;

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

    vector<Order *> *get_order_list();

private:
    vector<Order*> vec_order_list; //store the orders
};

void simulateAttack(Territory*, Territory*, Player*, int*);
