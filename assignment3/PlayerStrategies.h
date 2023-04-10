//
// Created by samue on 2023-04-10.
//

#ifndef ASSIGNMENT1_PLAYERSTRATEGIES_H
#define ASSIGNMENT1_PLAYERSTRATEGIES_H

#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "GameEngine.h"

class Player;


class PlayerStrategies {

public:
    virtual void issueOrder(Player *player, string orderType) = 0;
    virtual vector<Territory *> toAttack(Player *player) = 0;
    virtual vector<Territory *> toDefend(Player *player) = 0;

};

class HumanPlayer : public PlayerStrategies {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class AggressivePlayer : public PlayerStrategies {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class BenevolentPlayer : public PlayerStrategies {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class NeutralPlayer : public PlayerStrategies {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

#endif //ASSIGNMENT1_PLAYERSTRATEGIES_H
