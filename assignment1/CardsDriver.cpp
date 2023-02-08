#include "Cards.h"

int main() {
    //At beginning of the game make a deck for everyone
    Deck deck;
    //At beggining of the game make a deck for every player
    Hand hand;
    int in;
   // deck.printDeck();
    cout<<endl;
    cout<<endl;
    //populate hand with 5 card for testing
    for (int i = 0; i < 5; ++i) {
        if (!deck.isEmpty()) {
            hand.addToHand(deck.draw());
        }
        else{
            cout << "ERROR:  Cannot draw, Deck is Empty";
        }
    }
    cout<<endl;
    cout<<endl;
    //choose a card to play
    cout<<"Which card would you like to play? indicate by index: "<<endl;
    hand.printHand();
    cin>>in;

    cout<<endl;
    cout<<endl;
    //remove card from hand to play it
    hand.remFromHand(in).play();
    cout<<"Cards left in hand : "<<endl;
    hand.printHand();


}
