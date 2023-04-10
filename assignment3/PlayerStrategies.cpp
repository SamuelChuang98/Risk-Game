//
// Created by samue on 2023-04-10.
//

#include "PlayerStrategies.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>


/*Using the Strategy design pattern, implement different kinds of players that make different decisions during the
issuing orders phase by implementing different versions of issueOrder(), toAttack() and toDefend() in
different ConcreteStrategy classes, whose respective behaviors are described below. The kinds of players are:
• Human player: requires user interactions to make decisions.
• Aggressive player: computer player that focuses on attack (deploys or advances armies on its strongest
country, then always advances to enemy territories until it cannot do so anymore).
• Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies
on its weakest countries, never advances to enemy territories).
• Neutral player: computer player that never issues any order. If a Neutral player is attacked, it becomes an
Aggressive player.
• Cheater player: computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn).
You must deliver a driver that demonstrates that (1) different players can be assigned different strategies that lead
to different behavior using the Strategy design pattern; (2) the strategy adopted by a player can be changed
dynamically during play, (3) the human player makes decisions according to user interaction, and computer
players make decisions automatically, which are both implemented using the strategy pattern. The code for the
Strategy class and its ConcreteStrategies must be implemented in a new
PlayerStrategies.cpp/PlayerStrategies.h file duo. In order to have a real strategy implementation, the
following conditions must be present in your resulting implementation:
• Your Player class does not have subclasses that implement different behaviors.
• You have a PlayerStrategy abstract class that is not a subclass of the Player class.
• For each strategy as described above, you have a ConcreteStrategy class: HumanPlayerStrategy,
AggressivePlayerStrategy, BenevolentPlayerStrategy, and NeutralPlayerStrategy that are
subclasses of the PlayerStrategy class.
• Each of the ConcreteStrategy classes implement their own version of the issueOrder(), toAttack(), and
toDefend() methods.
• The Player class contains a data member of type PlayerStrategy.
• The issueOrder(), toDefend(), and toAttack() methods of the player do not implement behavior and
simply delegate their call to the corresponding methods in the PlayerStrategy member of the Player. */


void HumanPlayerStrategy::issueOrder(Player *player, string orderType) {
    cout << "HumanPlayerStrategy::issueOrder()" << endl;
    if (orderType == "deploy") {
        cout << "Enter the territory you want to deploy to: " << endl;
        int territoryId;
        cin >> territoryId;
        cout << "Enter the number of armies you want to deploy: " << endl;
        int numArmies;
        cin >> numArmies;
        player->issueOrder(new Deploy(player, player->getTerritory(territoryId), numArmies));
    } else if (orderType == "advance") {
        cout << "Enter the territory you want to advance from: " << endl;
        int sourceTerritoryId;
        cin >> sourceTerritoryId;
        cout << "Enter the territory you want to advance to: " << endl;
        int targetTerritoryId;
        cin >> targetTerritoryId;
        cout << "Enter the number of armies you want to advance: " << endl;
        int numArmies;
        cin >> numArmies;
        player->issueOrder(new Advance(player, player->getTerritory(sourceTerritoryId),
                                       player->getTerritory(targetTerritoryId), numArmies));
    } else if (orderType == "bomb") {
        cout << "Enter the territory you want to bomb: " << endl;
        int territoryId;
        cin >> territoryId;
        player->issueOrder(new Bomb(player, player->getTerritory(territoryId)));
    } else if (orderType == "blockade") {
        cout << "Enter the territory you want to blockade: " << endl;
        int territoryId;
        cin >> territoryId;
        player->issueOrder(new Blockade(player, player->getTerritory(territoryId)));
    } else if (orderType == "airlift") {
        cout << "Enter the territory you want to airlift from: " << endl;
        int sourceTerritoryId;
        cin >> sourceTerritoryId;
        cout << "Enter the territory you want to airlift to: " << endl;
        int targetTerritoryId;
        cin >> targetTerritoryId;
        cout << "Enter the number of armies you want to airlift: " << endl;
        int numArmies;
        cin >> numArmies;
        player->issueOrder(new Airlift(player, player->getTerritory(sourceTerritoryId),
                                       player->getTerritory(targetTerritoryId), numArmies));
    } else if (orderType == "negotiate") {
        cout << "Enter the player you want to negotiate with: " << endl;
        string playerName;
        cin >> playerName;
        player->issueOrder(new Negotiate(player, player->getGame()->getPlayer(playerName)));
    }
}

void HumanPlayerStrategy::toAttack(Player *player) {
    cout << "HumanPlayerStrategy::toAttack()" << endl;
    cout << "Enter the territory you want to attack from: " << endl;
    int sourceTerritoryId;
    cin >> sourceTerritoryId;
    cout << "Enter the territory you want to attack: " << endl;
    int targetTerritoryId;
    cin >> targetTerritoryId;
    cout << "Enter the number of armies you want to attack with: " << endl;
    int numArmies;
    cin >> numArmies;
    player->issueOrder(new Advance(player, player->getTerritory(sourceTerritoryId),
                                   player->getTerritory(targetTerritoryId), numArmies));
}

void HumanPlayerStrategy::toDefend(Player *player) {
    cout << "HumanPlayerStrategy::toDefend()" << endl;
    cout << "Enter the territory you want to defend: " << endl;
    int sourceTerritoryId;
    cin >> sourceTerritoryId;
    cout << "Enter the number of armies you want to defend with: " << endl;
    int numArmies;
    cin >> numArmies;
    player->issueOrder(new Advance(player, player->getTerritory(sourceTerritoryId),
                                   player->getTerritory(sourceTerritoryId), numArmies));
}

void AggressivePlayerStrategy::issueOrder(Player *player, string orderType) {
    cout << "AggressivePlayerStrategy::issueOrder()" << endl;
    if (orderType == "deploy") {
        Territory *strongestTerritory = player->getStrongestTerritory();
        player->issueOrder(new Deploy(player, strongestTerritory, strongestTerritory->getArmies() / 2));
    } else if (orderType == "advance") {
        Territory *strongestTerritory = player->getStrongestTerritory();
        Territory *targetTerritory = strongestTerritory->getStrongestAdjacentEnemyTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Advance(player, strongestTerritory, targetTerritory,
                                           strongestTerritory->getArmies() / 2));
        }
    } else if (orderType == "bomb") {
        Territory *strongestTerritory = player->getStrongestTerritory();
        Territory *targetTerritory = strongestTerritory->getStrongestAdjacentEnemyTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Bomb(player, targetTerritory));
        }
    } else if (orderType == "blockade") {
        Territory *strongestTerritory = player->getStrongestTerritory();
        player->issueOrder(new Blockade(player, strongestTerritory));
    } else if (orderType == "airlift") {
        Territory *strongestTerritory = player->getStrongestTerritory();
        Territory *targetTerritory = strongestTerritory->getStrongestAdjacentEnemyTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Airlift(player, strongestTerritory, targetTerritory,
                                           strongestTerritory->getArmies() / 2));
        }
    } else if (orderType == "negotiate") {
        Player *weakestPlayer = player->getGame()->getWeakestPlayer();
        if (weakestPlayer != nullptr) {
            player->issueOrder(new Negotiate(player, weakestPlayer));
        }
    }
}

void AggressivePlayerStrategy::toAttack(Player *player) {
    cout << "AggressivePlayerStrategy::toAttack()" << endl;
    Territory *strongestTerritory = player->getStrongestTerritory();
    Territory *targetTerritory = strongestTerritory->getStrongestAdjacentEnemyTerritory();
    if (targetTerritory != nullptr) {
        player->issueOrder(new Advance(player, strongestTerritory, targetTerritory,
                                       strongestTerritory->getArmies() / 2));
    }
}

void AggressivePlayerStrategy::toDefend(Player *player) {
    cout << "AggressivePlayerStrategy::toDefend()" << endl;
    Territory *strongestTerritory = player->getStrongestTerritory();
    player->issueOrder(new Advance(player, strongestTerritory, strongestTerritory,
                                   strongestTerritory->getArmies() / 2));
}

void BenevolentPlayerStrategy::issueOrder(Player *player, string orderType) {
    cout << "BenevolentPlayerStrategy::issueOrder()" << endl;
    if (orderType == "deploy") {
        Territory *weakestTerritory = player->getWeakestTerritory();
        player->issueOrder(new Deploy(player, weakestTerritory, weakestTerritory->getArmies() / 2));
    } else if (orderType == "advance") {
        Territory *weakestTerritory = player->getWeakestTerritory();
        Territory *targetTerritory = weakestTerritory->getStrongestAdjacentFriendlyTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Advance(player, weakestTerritory, targetTerritory,
                                           weakestTerritory->getArmies() / 2));
        }
    } else if (orderType == "bomb") {
        Territory *weakestTerritory = player->getWeakestTerritory();
        Territory *targetTerritory = weakestTerritory->getStrongestAdjacentFriendlyTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Bomb(player, targetTerritory));
        }
    } else if (orderType == "blockade") {
        Territory *weakestTerritory = player->getWeakestTerritory();
        player->issueOrder(new Blockade(player, weakestTerritory));
    } else if (orderType == "airlift") {
        Territory *weakestTerritory = player->getWeakestTerritory();
        Territory *targetTerritory = weakestTerritory->getStrongestAdjacentFriendlyTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Airlift(player, weakestTerritory, targetTerritory,
                                           weakestTerritory->getArmies() / 2));
        }
    } else if (orderType == "negotiate") {
        Player *strongestPlayer = player->getGame()->getStrongestPlayer();
        if (strongestPlayer != nullptr) {
            player->issueOrder(new Negotiate(player, strongestPlayer));
        }
    }
}

void BenevolentPlayerStrategy::toAttack(Player *player) {
    cout << "BenevolentPlayerStrategy::toAttack()" << endl;
    Territory *weakestTerritory = player->getWeakestTerritory();
    Territory *targetTerritory = weakestTerritory->getStrongestAdjacentFriendlyTerritory();
    if (targetTerritory != nullptr) {
        player->issueOrder(new Advance(player, weakestTerritory, targetTerritory,
                                       weakestTerritory->getArmies() / 2));
    }
}

void BenevolentPlayerStrategy::toDefend(Player *player) {
    cout << "BenevolentPlayerStrategy::toDefend()" << endl;
    Territory *weakestTerritory = player->getWeakestTerritory();
    player->issueOrder(new Advance(player, weakestTerritory, weakestTerritory,
                                   weakestTerritory->getArmies() / 2));
}

void NeutralPlayerStrategy::issueOrder(Player *player, string orderType) {
    cout << "NeutralPlayerStrategy::issueOrder()" << endl;
    if (orderType == "deploy") {
        Territory *randomTerritory = player->getRandomTerritory();
        player->issueOrder(new Deploy(player, randomTerritory, randomTerritory->getArmies() / 2));
    } else if (orderType == "advance") {
        Territory *randomTerritory = player->getRandomTerritory();
        Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Advance(player, randomTerritory, targetTerritory,
                                           randomTerritory->getArmies() / 2));
        }
    } else if (orderType == "bomb") {
        Territory *randomTerritory = player->getRandomTerritory();
        Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Bomb(player, targetTerritory));
        }
    } else if (orderType == "blockade") {
        Territory *randomTerritory = player->getRandomTerritory();
        player->issueOrder(new Blockade(player, randomTerritory));
    } else if (orderType == "airlift") {
        Territory *randomTerritory = player->getRandomTerritory();
        Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Airlift(player, randomTerritory, targetTerritory,
                                           randomTerritory->getArmies() / 2));
        }
    } else if (orderType == "negotiate") {
        Player *randomPlayer = player->getGame()->getRandomPlayer();
        if (randomPlayer != nullptr) {
            player->issueOrder(new Negotiate(player, randomPlayer));
        }
    }
}

void NeutralPlayerStrategy::toAttack(Player *player) {
    cout << "NeutralPlayerStrategy::toAttack()" << endl;
    Territory *randomTerritory = player->getRandomTerritory();
    Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
    if (targetTerritory != nullptr) {
        player->issueOrder(new Advance(player, randomTerritory, targetTerritory,
                                       randomTerritory->getArmies() / 2));
    }
}

void NeutralPlayerStrategy::toDefend(Player *player) {
    cout << "NeutralPlayerStrategy::toDefend()" << endl;
    Territory *randomTerritory = player->getRandomTerritory();
    player->issueOrder(new Advance(player, randomTerritory, randomTerritory,
                                   randomTerritory->getArmies() / 2));
}

void CheaterPlayerStrategy::issueOrder(Player *player, string orderType) {
    cout << "CheaterPlayerStrategy::issueOrder()" << endl;
    if (orderType == "deploy") {
        Territory *randomTerritory = player->getRandomTerritory();
        player->issueOrder(new Deploy(player, randomTerritory, randomTerritory->getArmies() * 2));
    } else if (orderType == "advance") {
        Territory *randomTerritory = player->getRandomTerritory();
        Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Advance(player, randomTerritory, targetTerritory,
                                           randomTerritory->getArmies() * 2));
        }
    } else if (orderType == "bomb") {
        Territory *randomTerritory = player->getRandomTerritory();
        Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Bomb(player, targetTerritory));
        }
    } else if (orderType == "blockade") {
        Territory *randomTerritory = player->getRandomTerritory();
        player->issueOrder(new Blockade(player, randomTerritory));
    } else if (orderType == "airlift") {
        Territory *randomTerritory = player->getRandomTerritory();
        Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
        if (targetTerritory != nullptr) {
            player->issueOrder(new Airlift(player, randomTerritory, targetTerritory,
                                           randomTerritory->getArmies() * 2));
        }
    } else if (orderType == "negotiate") {
        Player *randomPlayer = player->getGame()->getRandomPlayer();
        if (randomPlayer != nullptr) {
            player->issueOrder(new Negotiate(player, randomPlayer));
        }
    }
}

void CheaterPlayerStrategy::toAttack(Player *player) {
    cout << "CheaterPlayerStrategy::toAttack()" << endl;
    Territory *randomTerritory = player->getRandomTerritory();
    Territory *targetTerritory = randomTerritory->getRandomAdjacentTerritory();
    if (targetTerritory != nullptr) {
        player->issueOrder(new Advance(player, randomTerritory, targetTerritory,
                                       randomTerritory->getArmies() * 2));
    }
}

void CheaterPlayerStrategy::toDefend(Player *player) {
    cout << "CheaterPlayerStrategy::toDefend()" << endl;
    Territory *randomTerritory = player->getRandomTerritory();
    player->issueOrder(new Advance(player, randomTerritory, randomTerritory,
                                   randomTerritory->getArmies() * 2));
}


