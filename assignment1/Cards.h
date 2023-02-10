//
// Created by Ben on 2023-02-07.
//
#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
using namespace std;

enum cardType {
    bomb, reinforcement, blockade, airlift, diplomacy
};
namespace cardSpace {
    int cardsMain();
}
class Cards {
private:
    cardType type;
public:
    Cards();

    explicit Cards(cardType theType);

    cardType getType();

    void setType(cardType theType);

    void play(); // To implement using orders
    void printCard();

    bool equals(Cards card);

};

class Hand {
private:
    std::vector<Cards> cards;
public:
    Hand();

    void addToHand(Cards card);

    Cards remFromHand(int i);

    bool isEmpty();

    void printHand();
};

class Deck {
private:
    std::vector<Cards> cards;
public:
    Deck();

    Cards draw();

    bool isEmpty();

    void printDeck();
};

#endif //CARDS_H