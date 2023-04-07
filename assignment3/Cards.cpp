//
// Created by Ben on 2023-02-07.
//
#include "Cards.h"

//random engine
int currentDeckSize(51);
std::random_device dev;
std::mt19937 engine(dev());
std::uniform_int_distribution<> dis(0, 4); // Define the range
std::uniform_int_distribution<> das(0, currentDeckSize); // Define the range

/**
 * Card Class implementation
 */

//Default Constructor
Cards::Cards() { type = new cardType(diplomacy); }
//copy constructor
Cards::Cards(Cards &card) { type = new cardType(card.getType()); }
//param constructor
Cards::Cards(cardType *theType) { this->type = new cardType(*theType); }
//assignment operator
Cards& Cards::operator=(const Cards _c){
    delete type;
    type = new cardType(*_c.type);
    return *this;
}

//Destructor
Cards::~Cards(){
    delete type;
    type= NULL;
}
/**
 * getter
 * @return &type
 */
cardType Cards::getType() {
    return *type;
}
/**
 * setter
 * @param theType
 */
void Cards::setType(cardType &theType) {
    *type = theType;
}
// TODO implement using orders
void Cards::play() {
    cout << "Playing : ";
    this->printCard();
}
/**
 * prints out current card
 */
string Cards::printCard() {
    string theCard;
    switch (*type) {
        case bomb: theCard = "bomb";
            break;
        case reinforcement: theCard = "reinforcement";
            break;
        case blockade: theCard = "blockade";
            break;
        case airlift: theCard = "airlift";
            break;
        case diplomacy: theCard = "diplomacy";
            break;
        default: theCard = "null";
    }
    return theCard;
}
std::ostream& operator<<(std::ostream& strm,  Cards& c) { return strm << "Card(" << c.printCard()<< ")"; } // Stream assignment
/**
 * Hand Class implementation
 */
//Default constructor
Hand::Hand() = default;
//Copy constructor
Hand::Hand(Hand &hand) {
    for(Cards *car: hand.cards){
        this->cards.push_back(new Cards(*car));
    }
}
//assignment operator
Hand& Hand::operator=(const Hand _h){
    for(Cards *car: _h.cards){
        cards.push_back(car);
    }
    return *this;
}
//destructor
Hand::~Hand() {
    for(Cards *car: cards){
        delete car;
    }
    cards.clear();
}
/**
 * represents the action of drawing a card from the deck and putting it in a players hand
 * uses Cards copy constructor to push a new card on to the vector stack cards in hand
 * then prints out the cardType
 * @param card
 */
void Hand::addToHand(Cards &card) {
    cards.push_back(&card);
    cout << " Added to Hand: "<< card << endl;
}
/**
 *  * represents the action of removing a card from the players hand.
 * create a new card pointer, when the index at the position of the hand is
 * found use copy constructor to initialize the new card and erase current position in
 * hand and return copied card reference
 * @param index
 * @return &card
 */
Cards &Hand::remFromHand(int index) {
    index--;
    Cards *card;
    for (int i = 0; i < cards.size(); ++i) {
        if (index == i) {
            card = new Cards(*cards.at(i));
            cards.erase(cards.begin() + i);
        }
    }
    return *card;
}
//print current hand of cards
void Hand::printHand() {
    for (int i = 0; i < cards.size(); ++i) {
        cout << (i + 1) << " ";
        cards.at(i)->printCard();
    }
}
std::ostream& operator<<(std::ostream& strm, const Hand& h) {
    int i = 1;
    strm << "Cards[" << endl;
    for(Cards* car : h.cards){
        strm << i << " : " << car->printCard() << endl;
        ++i;
    }
    strm << "]";
    return strm;
} // Stream assignment
/**
 * Deck Class implementation
 */
// Default constructor, Initialize deck object with 52 randomly generated cards
Deck::Deck() {
    int random;
    for (int i = 0; i < 52; i++) {
        random = dis(engine);
        cardType *type = new cardType(static_cast<cardType>(random));
        Cards *card = new Cards(type);
        cards.push_back(card);
    }
}
//Copy constructor
Deck::Deck(Deck &deck) {
    for(Cards *car: deck.cards){
        this->cards.push_back(new Cards(*car));
    }
}
//destructor
Deck::~Deck() {
    for(Cards *car: cards){
        delete car;
    }
    cards.clear();
}

/**
 * represents the action of picking up a card from the deck and returning it,
 * initializes a pointer using Cards copy constructor of a card at the random position
 * of the current deck size from cards vector, then erases it and returns the copied card
 * @return *card
 */
Cards *Deck::draw() {
    int theLuckyOne = das(engine);
    Cards *card = new Cards(*cards.at(theLuckyOne));
    cards.erase(cards.begin() + theLuckyOne);
    --currentDeckSize;
    return card;
}
//check if deck is empty
bool Deck::isEmpty() { return cards.empty();}
//prints deck
void Deck::printDeck() {
    for (int i = 0; i < cards.size(); ++i) {
        cout << (i + 1) << " ";
        cards.at(i)->printCard();
    }
}
std::ostream& operator<<(std::ostream& strm, const Deck& d) {
    strm << "Cards[" << endl;
    for(Cards* car : d.cards){
        strm << car->printCard() << endl;
    }
    strm << "]";
    return strm;
} // Stream assignment
