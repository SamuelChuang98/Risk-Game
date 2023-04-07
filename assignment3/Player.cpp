#include <iostream>
#include <vector>

#include "Player.h"

// Default constructor
Player::Player()
{
    hand = new Hand();
    orders = new OrderList();
}

// Param. constructor
Player::Player(int pID, vector<Territory*> ters, Hand* hand, OrderList* orders, int reinforcementPool, bool hasContinentBonus)
{
    this->pID = pID;

    for (Territory* ter : ters) {
        this->ters.push_back(new Territory(*ter));
    }

    this->hand = new Hand(*hand);

    this->orders = new OrderList();

    this->reinforcementPool = reinforcementPool;

    this->hasContinentBonus = false;
}

// Copy constructor - performs deep copy
Player::Player(Player& p)
{
    this->pID = p.pID;

    for (Territory* ter : p.ters) {
        this->ters.push_back(new Territory(*ter));
    }

    this->hand = new Hand(*p.hand);

    orders = new OrderList(*p.orders);

    this->reinforcementPool = p.reinforcementPool;

    this->hasContinentBonus = p.hasContinentBonus;

}


// Destructor
Player::~Player()
{
    // Delete dynamically allocated territories pointed to in ters vector
    for (Territory* ter : ters) {
        delete ter;
    }
    ters.clear();    // Remove pointers from ters

    /* for (string *hand: hands) {
         delete hand;
     }
     hands.clear();*/
    delete hand;
    hand = NULL;

    delete orders;
    orders = NULL;
}

// Assignment operator - performs shallow copy
Player& Player::operator=(const Player& rightSide) {
    this->ters = rightSide.ters;
    this->hand = rightSide.hand;
    this->orders = rightSide.orders;
    this->reinforcementPool = rightSide.reinforcementPool;
    return *this;
}

// Hand* Player::getHand()
// {
//     return hand;
// }

// OrderList* Player::getOrders()
// {
//     return orders;
// }

// Stream insertion operator, returns player's first territory as a stream
std::ostream& operator<<(std::ostream& strm, const Player& p) {
    return strm << "Player(" << p.ters.at(0)->getTerritoryName() << ")";
}

// Get territories a player must defend
vector<Territory*> Player::toDefend() {

    vector<Territory*> defenseTers;

    cout << "List of territories to defend: " << endl;

    // push territories owned by player to a new vector
    for (int i = 0; i < ters.size(); i++) {
        cout << ters[i]->getTerritoryName() << endl;
        defenseTers.push_back(ters[i]);
    }

    return defenseTers;
}

// Get territories a player must attack
vector<Territory*> Player::toAttack() {
    vector<Territory*> attackTers;

    // Return the other half of territories from this player for now.
    for (int i = 1; i < ters.size(); i = i + 2) {
        attackTers.push_back(ters.at(i));
    }

    return attackTers;
}

void Player::issueOrder(vector<Territory*> t)
{
    Order* order = new Order();
    orders->set_order_list(order);

    vector<Territory*> defend = toDefend();
    vector<Territory*> attack = toAttack();

    // Deploy armies until none are left
    while (getReinforcementPool() != 0)
    {
        int armiesToDeploy = getReinforcementPool();
        int toDeploy = 0;

        for (int i = 0; i < defend.size(); i++)
        {

            // get user input
            cout << "Territory: " << defend[i]->getTerritoryName() << endl;
            cout << "How many armies do you want to deploy to this territory: " << endl;
            cin >> toDeploy;

            // if only one army is remaining to deploy
            if (armiesToDeploy == 1)
            {
                defend[i]->setNumberOfArmies(defend[i]->getNumberOfArmies() + 1);
                setReinforcementPool(0);
            }
            else {
                defend[i]->setNumberOfArmies(defend[i]->getNumberOfArmies() + toDeploy);
                setReinforcementPool(getReinforcementPool() - toDeploy);
            }
        }

    }
}

// check if a continent is controlled by one player
bool Player::ContinentBonus(vector<Territory*> c)
{
    bool samePlayer = false;

    for (int i = 0; i < c.size(); i++) {
        for (int k = i + 1; c.size(); k++) {
            if (k == c.size()) {
                break;
            }
            if (c[i]->getPlayer() == c[k]->getPlayer()) {
                samePlayer = true;
            }
            else {
                return false;
            }
        }
    }

    return samePlayer;
}

void Player::addFriendly(Player& p) {
    friendlies.push_back(&p);
}

//

int Player::getPiD()
{
    return this->pID;
}

vector<Territory*> Player::getTerritories()
{
    return this->ters;
}

Hand* Player::getHand()
{
    return this->hand;
}

OrderList* Player::getOrders()
{
    return this->orders;
}

int Player::getReinforcementPool()
{
    return this->reinforcementPool;
}

bool Player::getContinentBonus() {
    return this->hasContinentBonus;
}

int Player::getPlayerID() {
    return this->getPlayerID();
}

vector<Player*> Player::getFriendlies() {
    return friendlies;
}

// Mutators

void Player::setPiD(int pID)
{
    this->pID = pID;
}

void Player::setPlayerID(int playerId)
{
    this->playerID = playerId;
}

void Player::setTerritories(vector<Territory*> ters)
{
    this->ters = ters;
}

void Player::setHand(Hand* hand)
{
    this->hand = hand;
}

void Player::setOrders(OrderList* orders)
{
    this->orders = orders;
}

void Player::setReinforcementPool(int reinforcement)
{
    this->reinforcementPool = reinforcement;
}

void Player::setContinentBonus(bool CB) {
    this->hasContinentBonus = CB;
}

string Player::getPlayerName()
{
    return playerName;
}

void Player::setPlayerName(string playerName)
{
    this->playerName = playerName;
}