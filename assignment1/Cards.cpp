//
// Created by Ben on 2023-02-07.
//
#include "Cards.h"

/**
 * Card Class implementation
 */
std::random_device dev;
std::mt19937 engine(dev());
std::uniform_int_distribution<> dis(0, 4); // Define the range
std::uniform_int_distribution<> das(0, 51); // Define the range

 //Default Constructor
Cards::Cards() { Cards ::setType(diplomacy); }

Cards::Cards(cardType theType) { Cards ::setType(theType); }


cardType Cards::getType() {
    return Cards::type;
}

void Cards::setType(cardType theType) {
    Cards::type = theType;
}

void Cards::play() {
    cout << "Playing : ";
    this->printCard();
}

void Cards::printCard() {
    switch (type) {
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
// cout << "Current card : " << Cards :: getType() << endl;
}

bool Cards::equals(Cards card) {
    return type == card.getType();
}

/**
 * Hand Class implementation
 */
Hand::Hand() = default;

//represents the action of drawing a card from the deck and putting it in a players hand
void Hand::addToHand(Cards card) {
    cards.push_back(card);
    cout << " You got card: ";
    card.printCard();
}

//represents the action of removing a card from the players hand, removes first instance of chosen card from hand and returns it
Cards Hand::remFromHand(int index) {
    index--;
    Cards card;
    for (int i = 0; i < cards.size(); ++i) {
        if (index == i) {
            card = cards.at(i);
            cards.erase(cards.begin() + i);
        }
    }
    return card;
}

bool Hand::isEmpty() {
    return cards.empty();
}

void Hand::printHand() {
    for (int i = 0; i < cards.size(); ++i) {
        cout << (i + 1) << " ";
        cards.at(i).printCard();
    }
}


/**
 * Deck Class implementation
 */
//Initialize deck object with 52 randomly generated cards
Deck::Deck() {
    int random;


    for (int i = 0; i < 52; i++)
    {
        random = dis(engine);
        auto type = static_cast<cardType>(random);
        Cards card(type);
        cards.push_back(card);
    }
}

//represents the action of picking up a card from the deck, removes one random card from deck and returns it
Cards Deck::draw() {

    int theLuckyOne = das(engine);
    Cards card( cards.at( theLuckyOne));
    cards.erase(cards.begin() + theLuckyOne);
    return card;
}

bool Deck::isEmpty() {
    return cards.empty();
}

void Deck::printDeck() {
    for (int i = 0; i < cards.size(); ++i) {
        cout << (i + 1) << " ";
        cards.at(i).printCard();
    }
}
