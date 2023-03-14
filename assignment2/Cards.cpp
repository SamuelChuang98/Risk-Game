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
void Cards::printCard() {
    switch (*type) {
        case bomb:
            cout << " bomb" << endl;
            break;
        case reinforcement:
            cout << " reinforcement" << endl;
            break;
        case blockade:
            cout << " blockade" << endl;
            break;
        case airlift:
            cout << " airlift" << endl;
            break;
        case diplomacy:
            cout << " diplomacy" << endl;
            break;
        default:
            cout << "Current card : is null" << endl;
    }
}
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
    cout << " You got card: ";
    card.printCard();
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
