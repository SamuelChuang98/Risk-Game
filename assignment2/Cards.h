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
    cardType *type;
    friend std::ostream &operator<<(std::ostream &strm, const Cards &c); //Stream insertion
public:
    //Default constructor
    Cards();
    //copy constructor
    Cards(Cards &card);
    //param constructor
    Cards(cardType *theType);
    //assignment operator
    Cards& operator=(const Cards _c);
    //destructor
    ~Cards();
    //getter
    cardType getType();

    void setType(cardType &theType);

    void play(); // To implement using orders
    string printCard();

};

class Hand {
private:
    std::vector<Cards *> cards;
    friend std::ostream &operator<<(std::ostream &strm, const Hand &h); //Stream insertion
public:
    //Default constructor
    Hand();
    //copy constructor
    Hand(Hand &hand);
    //assignment operator
    Hand& operator=(const Hand _h);
    //destructor
    ~Hand();
    /*
     * represents the action of drawing a card from the deck and putting it in a players hand
     * uses Cards parameterized constructor to push a new card on to the vector stack cards
     * then prints out the cardType
     */
    void addToHand(Cards &card);

    /*
     * represents the action of removing a card from the players hand.
    * removes first instance of chosen card from hand and returns it.
    *
    */
    Cards &remFromHand(int i);

    void printHand();
};

class Deck {
private:
    std::vector<Cards *> cards;
    friend std::ostream &operator<<(std::ostream &strm, const Deck &d); //Stream insertion
public:
    //default constructor
    Deck();
    //copy constructor
    Deck(Deck &deck);
    //destructor
    ~Deck();
    /*
     * represents the action of picking up a card from the deck and returning it,
     * initializes a pointer using Cards copy constructor of a card at the random position
     * of the current deck size from cards vector, then erases it and returns the copied card
     */
    Cards *draw();

    bool isEmpty();
    //print contents of deck
    void printDeck();
};

#endif //CARDS_H