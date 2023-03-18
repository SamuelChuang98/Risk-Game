#include "Orders.h"
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

using std::cout;
using std::endl;

Order::Order(){
    thisPlayer=nullptr;
}
Order::~Order(){
    thisPlayer = nullptr;
}

//This validates the order
/*void Order::validate()
{
	cout << "Validating order..." << endl;
	valid = true;
}*/

//This executes the order
void Order::execute()
{

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

void OrderList::execute_orders()
{
    int listSize = vec_order_list.size();

    if (listSize == 0)
        cout << "No orders to execute!" << endl;
    else
    {
        for (int i = 0; i < listSize; i++)
        {
            vec_order_list[i]->execute();
            delete vec_order_list[i];
        }

        vec_order_list.clear();
        cout << "Execution completed!" << endl;
    }
}

//OrderList copy constructor
OrderList::OrderList(OrderList const &other)
{
    // Copy the vector of Order pointers
    vec_order_list = *(other.get_order_list());

    // Create copies of the Order objects and update the vector to point to the copies
    for (int i = 0; i < vec_order_list.size(); i++)
    {
        vec_order_list[i] = new Order(*vec_order_list[i]);
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

Deploy::~Deploy(){
    delete amount;
}

string* Deploy::get_type()
{
    return &type1;
}

// Copy constructor
Deploy::Deploy(const Deploy& other)
{
    // Copy the member variables
    currentPlayer = other.currentPlayer;
    target = other.target;
    amount = new int(*other.amount);
}

Advance::Advance()
{
    set_id(1);
    validate();
    execute();
}

Advance::~Advance(){
    delete amount;
}

// Copy constructor
Advance::Advance(const Advance& other)
{
    // Copy the member variables
    source = other.source;
    target = other.target;
    amount = new int(*other.amount);
}

Bomb::Bomb()
{
    set_id(2);
    validate();
    execute();
}

Bomb::~Bomb(){}


// Copy constructor
Bomb::Bomb(const Bomb& other)
{
    // Copy the member variables
    target = other.target;
}

Blockade::Blockade()
{
    set_id(3);
    validate();
    execute();
}

Blockade::~Blockade(){}

// Copy constructor
Blockade::Blockade(const Blockade& other)
{
    // Copy the member variables
    target = other.target;
}

Airlift::Airlift()
{
    set_id(4);
    validate();
    execute();
}

Airlift::~Airlift(){
    delete amount;
}


// Copy constructor
Airlift::Airlift(const Airlift& other)
{
    // Copy the member variables
    source = other.source;
    target = other.target;
    amount = new int(*other.amount);
}

Negotiate::Negotiate()
{
    set_id(5);
    validate();
    execute();
}

Negotiate::~Negotiate(){}

// Copy constructor
Negotiate::Negotiate(const Negotiate& other)
{
    // Copy the member variables
    targetPlayer = other.targetPlayer;
}

// =============================== Validate of each order begins here =======================

bool Deploy::validate() const
{
    cout << "Validating Deploy...\n";

    //If the target territory does not belong to the player that issued the order, the order is invalid
    if (target->getTerritoryPlayerID() != thisPlayer->getPlayerID())
    {
        cout << "You do not own this territory!\n" << endl;
        return false;
    }

    //If the player doesn't have enough army
    else if (*amount > thisPlayer->getReinforcementPool())
    {
        cout << "You do not have this many armies in the reinforcement pool!\n" << endl;
        return false;
    }

    //If the amount requested is equal or lower than 0
    else if (*amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }

    return true;
}

bool Advance::validate() const
{
    cout << "Validating Advance...\n";

    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if (source->getTerritoryPlayerID() != thisPlayer->getPlayerID())
    {
        cout << "The source territory is not your own!\n" << endl;
        return false;
    }

    //If the target territory is not adjacent to the source territory, the order is invalid.
    else if (!source->isAdjacent(target))
    {
        cout << "The target territory is not adjacent to the source territory!\n" << endl;
        return false;
    }

    //If the player doesn't have enough army
    else if (*amount > source->getNumberOfArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
        return false;
    }

    //If the amount requested is equal or lower than 0
    else if (*amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }

    return true;
}

bool Airlift::validate() const
{
    cout << "Validating Airlift...\n";

    //The target territory does not need to be adjacent to the source territory.

    //If the source or target does not belong to the player that issued the order, the order is invalid.
    if (source->getTerritoryPlayerID() != thisPlayer->getPlayerID() && target -> getTerritoryPlayerID() != thisPlayer->getPlayerID())
    {
        cout << "The source and/or target territory is not your own!\n" << endl;
        return false;
    }

    else if (*amount > source->getNumberOfArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
    }

    else if (*amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }


    return true;
}

bool Bomb::validate() const
{
    cout << "Validating Bomb...\n";

    //If the target belongs to the player that issued the order, the order is invalid.
    if(target->getTerritoryPlayerID() == thisPlayer->getPlayerID())
    {
        cout << "This territory is your own!\n" << endl;
        return false;
    }

    //If the target territory is not adjacent to one of the territory owned by the player issuing the order, then the order is invalid.
    else if (!target->isAdjacent( /** Insert player territory list here **/))
    {
        cout << "The target territory is not adjacent to the source territory!\n" << endl;
        return false;
    }

    return true;
}

bool Blockade::validate() const
{
    cout << "Validating Blockade...\n";

    //If the target territory belongs to an enemy player, the order is declared invalid
    if(target->getTerritoryPlayerID() != thisPlayer->getPlayerID())
    {
        cout << "This is not your territory! This order can only be played on your own territory!\n" << endl;
        return false;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

bool Negotiate::validate() const
{
    cout << "Validating Negotiate...\n";

    if(targetPlayer->getPlayerID() == thisPlayer->getPlayerID())
    {
        cout << "You cannot negotiate with yourself!\n" << endl;
        return false;
    }

    cout << "Your order has been validated!\n" << endl;

    return true;
}

// ===================================== Execute method for each order ======================================

void Deploy::execute() const
{
    if (validate())
    {
        cout << "Deploying...\n";

        //the selected number of armies is added to the number of armies on that territory.
        target->setNumberOfArmies(*amount + target->getNumberOfArmies());
    }
}

void Advance::execute() const
{
    if (validate())
    {
        cout << "Advancing... \n";

        //If the source and target territory both belong to the player that issued the order, the army units are moved from the source to the target territory.
        if (source->getTerritoryPlayerID() == target->getTerritoryPlayerID())
        {
            source->setNumberOfArmies(source->getNumberOfArmies() - *amount);
            target->setNumberOfArmies(target->getNumberOfArmies() + *amount);
        }

        // If the target territory belongs to another player than the player that issued the advance order
        else
        {
            vector<Territory*> attackableTerritories = thisPlayer->toAttack();
            bool canAttack = false;
            for (Territory* t : attackableTerritories) {
                if (t == target) {
                    canAttack = true;
                    break;
                }
            }
            if (!canAttack) {
                cout << "You cannot attack this territory!" << endl;
                return;
            }

            simulateAttack(source, target, thisPlayer, amount);
        }

    }
}

void Airlift::execute() const
{
    if (validate())
    {

        vector<Territory*> attackableTerritories = thisPlayer->toAttack();
        bool canAttack = false;
        // if player can't attack the territory
        //if (!thisPlayer->canAttack(target->getTerritoryPlayerID()))
        for (Territory* t : attackableTerritories) {
            if (t == target) {
                canAttack = true;
                break;
            }
        }
        if (!canAttack) {
            cout << "You cannot attack this territory!" << endl;
            return;
        }

        cout << "Airlifting... \n";

        //If both the source and target territories belong to the player that issue the airlift order
        if (source->getTerritoryPlayerID() == target->getTerritoryPlayerID())
        {
            source->setNumberOfArmies(source->getNumberOfArmies() - *amount);
            target->setNumberOfArmies(target->getNumberOfArmies() + *amount);
        }

    }
}

void Bomb::execute() const
{
    if (validate())
    {
        vector<Territory*> attackableTerritories = thisPlayer->toAttack();
        bool canAttack = false;
        for (Territory* t : attackableTerritories) {
            if (t == target) {
                canAttack = true;
                break;
            }
        }
        if (!canAttack) {
            cout << "You cannot attack this territory!" << endl;
            return;
        }


        cout << "Bombing... \n";
        // If the target belongs to an enemy player, half of the armies are removed from this territory
        target->setNumberOfArmies(target->getNumberOfArmies() / 2);
    }
}

void Blockade::execute() const
{
    if (validate())
    {
        cout << "Blocking... \n";

        //If the target territory belongs to the player issuing the order, (Else of the validate statement)
        target->setNumberOfArmies(target->getNumberOfArmies() * 2);

        //the ownership of the territory is transferred to the Neutral player
        target->setTerritoryPlayerID(-1);
    }
}

void Negotiate::execute() const
{
    if (validate())
    {
        cout << "Negotiating... \n";
        //If the target is an enemy player (Else of the validate statement)

        thisPlayer->addFriendly(targetPlayer->getPlayerID());
        targetPlayer->addFriendly(thisPlayer->getPlayerID());
    }

}

void simulateAttack(Territory* source, Territory* target, Player* thisPlayer, int* amount){

    //Removes the army from source (movement)
    source->setNumberOfArmies(source->getNumberOfArmies() - *amount);

    srand(time(NULL));
    int defKills = 0; // Num of dead defense
    int attKills = 0; // Num of dead offense

    // Each attacking army unit involved has 60% chances of killing one defending army.
    for (int i=0; i < *amount ; i++){

        //Rand num between 1 - 100
        int roll = rand() % 100 + 1;

        if (roll <= 60){
            defKills++;
        }
    }

    // At the same time, each defending army unit has 70% chances of killing one attacking army unit.
    for (int i=0; i < *amount ; i++){

        //Rand num between 1 - 100
        int roll = rand() % 100 + 1;

        if (roll <= 70){
            attKills++;
        }
    }

    int targetArmyNum = target ->getNumberOfArmies() - defKills;
    int sourceArmyNum = *amount - attKills;

    if (targetArmyNum < 0){
        targetArmyNum = 0;
    }

    if (sourceArmyNum < 0){
        sourceArmyNum = 0;
    }

    // If all the defender's armies are eliminated, the attacker captures the territory. The attacking army units that survived the battle then occupy the conquered territory.
    // A player receives a card at the end of his turn if they successfully conquered at least one territory during their turn.
    if(targetArmyNum == 0 && sourceArmyNum > 0){
        cout << "Attackers win!" << endl;

        source -> setTerritoryPlayerID(thisPlayer->getPlayerID());
        thisPlayer -> getTerritoryList() -> push_back(target);
        target ->setNumberOfArmies(sourceArmyNum);
        thisPlayer -> getGE() -> Notify(); // Notify stats observer since a player conquered a territory

        // give thisPlayer 1 card
    }

    else{
        cout << "Attackers lost" << endl;
        source->setNumberOfArmies(source->getNumberOfArmies() + sourceArmyNum);
        target ->setNumberOfArmies(targetArmyNum);
    }




}