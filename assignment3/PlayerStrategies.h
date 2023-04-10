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


class PlayerStrategy {

public:
    virtual void issueOrder(Player *player, string orderType) = 0;
    virtual vector<Territory *> toAttack(Player *player) = 0;
    virtual vector<Territory *> toDefend(Player *player) = 0;

};

class HumanPlayerStrategy : public PlayerStrategy {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
    void issueOrder(Player *player, string orderType) override;
    vector<Territory *> toAttack(Player *player) override;
    vector<Territory *> toDefend(Player *player) override;

};

#endif //ASSIGNMENT1_PLAYERSTRATEGIES_H
