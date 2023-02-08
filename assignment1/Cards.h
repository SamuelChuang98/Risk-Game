//
// Created by Ben on 2023-02-07.
//
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

#ifndef CARDS_DECK_HAND_CARDS_H
#define CARDS_DECK_HAND_CARDS_H

#endif //CARDS_DECK_HAND_CARDS_H
using namespace std;

enum cardType {bomb, reinforcement, blockade, airlift, diplomacy};

class Cards{
    private:
        cardType type;
public:
        Cards();
        Cards(cardType theType);
        cardType getType();
        void setType( cardType theType );
        void play(); // To implement using orders
        void printCard();
        bool equals (Cards card);

};

class Hand{
    private:
        std :: vector<Cards> cards;
    public:
        Hand();
        void addToHand(Cards card);
        Cards remFromHand(int i);
        bool isEmpty();
        void printHand();
};

class Deck{
    private:
        std :: vector<Cards> cards;
    public:
        Deck();
        Cards draw();
        bool isEmpty();
        void printDeck();
};