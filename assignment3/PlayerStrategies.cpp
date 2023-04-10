//
// Created by samue on 2023-04-10.
//

#include "PlayerStrategies.h"

void HumanPlayer::issueOrder(Player *player, string orderType) {
    cout << "Human Player " << player->getPlayerName() << " is issuing an order." << endl;
    cout << "Please enter the order type you would like to issue: " << endl;
    cout << "1. Deploy" << endl;
    cout << "2. Advance" << endl;
    cout << "3. Bomb" << endl;
    cout << "4. Blockade" << endl;
    cout << "5. Airlift" << endl;
    cout << "6. Negotiate" << endl;
    cout << "7. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            orderType = "deploy";
            break;
        case 2:
            orderType = "advance";
            break;
        case 3:
            orderType = "bomb";
            break;
        case 4:
            orderType = "blockade";
            break;
        case 5:
            orderType = "airlift";
            break;
        case 6:
            orderType = "negotiate";
            break;
        case 7:
            orderType = "exit";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            issueOrder(player, orderType);
            break;
    }
    if (orderType == "deploy") {
        cout << "Please enter the territory you would like to deploy to: " << endl;
        string territoryName;
        cin >> territoryName;
        cout << "Please enter the number of armies you would like to deploy: " << endl;
        int numArmies;
        cin >> numArmies;
        Deploy *deploy = new Deploy(player, territoryName, numArmies);
        player->getOrders()->addOrder(deploy);
    } else if (orderType == "advance") {
        cout << "Please enter the territory you would like to advance from: " << endl;
        string fromTerritoryName;
        cin >> fromTerritoryName;
        cout << "Please enter the territory you would like to advance to: " << endl;
        string toTerritoryName;
        cin >> toTerritoryName;
        cout << "Please enter the number of armies you would like to advance: " << endl;
        int numArmies;
        cin >> numArmies;
        Advance *advance = new Advance(player, fromTerritoryName, toTerritoryName, numArmies);
        player->getOrders()->addOrder(advance);
    } else if (orderType == "bomb") {
        cout << "Please enter the territory you would like to bomb: " << endl;
        string territoryName;
        cin >> territoryName;
        Bomb *bomb = new Bomb(player, territoryName);
        player->getOrders()->addOrder(bomb);

    } else if (orderType == "blockade") {
        cout << "Please enter the territory you would like to blockade: " << endl;
        string territoryName;
        cin >> territoryName;
        Blockade *blockade = new Blockade(player, territoryName);
        player->getOrders()->addOrder(blockade);

    } else if (orderType == "airlift") {
        cout << "Please enter the territory you would like to airlift from: " << endl;
        string fromTerritoryName;
        cin >> fromTerritoryName;
        cout << "Please enter the territory you would like to airlift to: " << endl;
        string toTerritoryName;
        cin >> toTerritoryName;
        cout << "Please enter the number of armies you would like to airlift: " << endl;
        int numArmies;
        cin >> numArmies;
        Airlift *airlift = new Airlift(player, fromTerritoryName, toTerritoryName, numArmies);
        player->getOrders()->addOrder(airlift);

    } else if (orderType == "negotiate") {
        cout << "Please enter the player you would like to negotiate with: " << endl;
        string playerName;
        cin >> playerName;
        Negotiate *negotiate = new Negotiate(player, playerName);
        player->getOrders()->addOrder(negotiate);

    } else if (orderType == "exit") {
        cout << "Exiting..." << endl;
    } else {
        cout << "Invalid order type. Please try again." << endl;
        issueOrder(player, orderType);

    }
}

vector<Territory *> HumanPlayer::toAttack(Player *player) {
    cout << "Human Player " << player->getPlayerName() << " is deciding which territories to attack." << endl;
    cout << "Please enter the territory you would like to attack: " << endl;
    string territoryName;
    cin >> territoryName;
    vector<Territory *> territoriesToAttack;
    for (Territory *territory : player->getTerritories()) {
        if (territory->getTerritoryName() == territoryName) {
            territoriesToAttack.push_back(territory);
        }
    }
    
    return territoriesToAttack;
}

vector<Territory *> HumanPlayer::toDefend(Player *player) {
    cout << "Human Player " << player->getPlayerName() << " is deciding which territories to defend." << endl;
    cout << "Please enter the territory you would like to defend: " << endl;
    string territoryName;
    cin >> territoryName;
    vector<Territory *> territoriesToDefend;
    for (Territory *territory : player->getTerritories()) {
        if (territory->getTerritoryName() == territoryName) {
            territoriesToDefend.push_back(territory);
        }
    }
    return territoriesToDefend;
}

void AggressivePlayer::issueOrder(Player *player, string orderType) {
    cout << "Aggressive Player " << player->getPlayerName() << " is issuing an order." << endl;
    if (player->getTerritories().size() == 0) {
        cout << "Aggressive Player " << player->getPlayerName() << " has no territories to issue orders for." << endl;
    } else {
        cout << "Aggressive Player " << player->getPlayerName() << " is issuing a deploy order." << endl;
        Territory *strongestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() > strongestTerritory->getNumArmies()) {
                strongestTerritory = territory;
            }
        }
        int numArmies = strongestTerritory->getNumArmies();
        Deploy *deploy = new Deploy(player, strongestTerritory->getTerritoryName(), numArmies);
        player->getOrders()->addOrder(deploy);
        cout << "Aggressive Player " << player->getPlayerName() << " is issuing an advance order." << endl;
        Territory *weakestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() < weakestTerritory->getNumArmies()) {
                weakestTerritory = territory;
            }
        }
        int numArmiesToAdvance = strongestTerritory->getNumArmies() - 1;
        Advance *advance = new Advance(player, strongestTerritory->getTerritoryName(), weakestTerritory->getTerritoryName(), numArmiesToAdvance);
        player->getOrders()->addOrder(advance);
    }
}

vector<Territory *> AggressivePlayer::toAttack(Player *player) {
    cout << "Aggressive Player " << player->getPlayerName() << " is deciding which territories to attack." << endl;
    vector<Territory *> territoriesToAttack;
    if (player->getTerritories().size() == 0) {
        cout << "Aggressive Player " << player->getPlayerName() << " has no territories to attack." << endl;
    } else {
        Territory *strongestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() > strongestTerritory->getNumArmies()) {
                strongestTerritory = territory;
            }
        }
        territoriesToAttack.push_back(strongestTerritory);
    }
    return territoriesToAttack;
}

vector<Territory *> AggressivePlayer::toDefend(Player *player) {
    cout << "Aggressive Player " << player->getPlayerName() << " is deciding which territories to defend." << endl;
    vector<Territory *> territoriesToDefend;
    if (player->getTerritories().size() == 0) {
        cout << "Aggressive Player " << player->getPlayerName() << " has no territories to defend." << endl;
    } else {
        Territory *strongestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() > strongestTerritory->getNumArmies()) {
                strongestTerritory = territory;
            }
        }
        territoriesToDefend.push_back(strongestTerritory);
    }
    return territoriesToDefend;
}

void BenevolentPlayer::issueOrder(Player *player, string orderType) {
    cout << "Benevolent Player " << player->getPlayerName() << " is issuing an order." << endl;
    if (player->getTerritories().size() == 0) {
        cout << "Benevolent Player " << player->getPlayerName() << " has no territories to issue orders for." << endl;
    } else {
        cout << "Benevolent Player " << player->getPlayerName() << " is issuing a deploy order." << endl;
        Territory *weakestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() < weakestTerritory->getNumArmies()) {
                weakestTerritory = territory;
            }
        }
        int numArmies = weakestTerritory->getNumArmies();
        Deploy *deploy = new Deploy(player, weakestTerritory->getTerritoryName(), numArmies);
        player->getOrders()->addOrder(deploy);
        cout << "Benevolent Player " << player->getPlayerName() << " is issuing an advance order." << endl;
        Territory *strongestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() > strongestTerritory->getNumArmies()) {
                strongestTerritory = territory;
            }
        }
        int numArmiesToAdvance = strongestTerritory->getNumArmies() - 1;
        Advance *advance = new Advance(player, strongestTerritory->getTerritoryName(), weakestTerritory->getTerritoryName(), numArmiesToAdvance);
        player->getOrders()->addOrder(advance);
    }
}

vector<Territory *> BenevolentPlayer::toAttack(Player *player) {
    cout << "Benevolent Player " << player->getPlayerName() << " is deciding which territories to attack." << endl;
    vector<Territory *> territoriesToAttack;
    if (player->getTerritories().size() == 0) {
        cout << "Benevolent Player " << player->getPlayerName() << " has no territories to attack." << endl;
    } else {
        Territory *weakestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() < weakestTerritory->getNumArmies()) {
                weakestTerritory = territory;
            }
        }
        territoriesToAttack.push_back(weakestTerritory);
    }
    return territoriesToAttack;
}

vector<Territory *> BenevolentPlayer::toDefend(Player *player) {
    cout << "Benevolent Player " << player->getPlayerName() << " is deciding which territories to defend." << endl;
    vector<Territory *> territoriesToDefend;
    if (player->getTerritories().size() == 0) {
        cout << "Benevolent Player " << player->getPlayerName() << " has no territories to defend." << endl;
    } else {
        Territory *weakestTerritory = player->getTerritories()[0];
        for (Territory *territory : player->getTerritories()) {
            if (territory->getNumArmies() < weakestTerritory->getNumArmies()) {
                weakestTerritory = territory;
            }
        }
        territoriesToDefend.push_back(weakestTerritory);
    }
    return territoriesToDefend;
}

void NeutralPlayer::issueOrder(Player *player, string orderType) {
    cout << "Neutral Player " << player->getPlayerName() << " is issuing an order." << endl;
    if (player->getTerritories().size() == 0) {
        cout << "Neutral Player " << player->getPlayerName() << " has no territories to issue orders for." << endl;
    } else {
        cout << "Neutral Player " << player->getPlayerName() << " is issuing a deploy order." << endl;
        Territory *randomTerritory = player->getTerritories()[rand() % player->getTerritories().size()];
        int numArmies = randomTerritory->getNumArmies();
        Deploy *deploy = new Deploy(player, randomTerritory->getTerritoryName(), numArmies);
        player->getOrders()->addOrder(deploy);
        cout << "Neutral Player " << player->getPlayerName() << " is issuing an advance order." << endl;
        Territory *randomTerritory2 = player->getTerritories()[rand() % player->getTerritories().size()];
        int numArmiesToAdvance = randomTerritory->getNumArmies() - 1;
        Advance *advance = new Advance(player, randomTerritory->getTerritoryName(), randomTerritory2->getTerritoryName(), numArmiesToAdvance);
        player->getOrders()->addOrder(advance);
    }
}

vector<Territory *> NeutralPlayer::toAttack(Player *player) {
    cout << "Neutral Player " << player->getPlayerName() << " is deciding which territories to attack." << endl;
    vector<Territory *> territoriesToAttack;
    if (player->getTerritories().size() == 0) {
        cout << "Neutral Player " << player->getPlayerName() << " has no territories to attack." << endl;
    } else {
        Territory *randomTerritory = player->getTerritories()[rand() % player->getTerritories().size()];
        territoriesToAttack.push_back(randomTerritory);
    }
    return territoriesToAttack;
}

vector<Territory *> NeutralPlayer::toDefend(Player *player) {
    cout << "Neutral Player " << player->getPlayerName() << " is deciding which territories to defend." << endl;
    vector<Territory *> territoriesToDefend;
    if (player->getTerritories().size() == 0) {
        cout << "Neutral Player " << player->getPlayerName() << " has no territories to defend." << endl;
    } else {
        Territory *randomTerritory = player->getTerritories()[rand() % player->getTerritories().size()];
        territoriesToDefend.push_back(randomTerritory);
    }
    return territoriesToDefend;
}

