#include "cardDeck.cpp"
#include <vector>
#include <stdlib.h>
#include <stack>
#include <set>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
using namespace std;

class Test{
    public:
    list<Card> deck;
    array<list<Card>, 7> lowerPiles;

    Test(){
        init();
        // TEST METHODS
        test_makePiles();
    }

    void init(){
        // Create a Shuffled Deck
        cardDeck shuffDeck = cardDeck();
        deck = shuffDeck.shuffled;

        // Make the lower Piles
        list<Card> pile;
        for(int i = 0; i < 7; i++){
            pile.clear();
            for(int j=0; j<i+1; j++){
                pile.push_front(deck.front());
                deck.pop_front();
            }
            pile.front().setVis();
            lowerPiles[i] = pile;
	    }
    }


    // ============ TESTS ============
    void test_makePiles(){
        cout << "=============== NOW TESTING MAKE_PILES ===============" << endl;

        // Tests whether the lower piles are initialized correctly
        for(int i=0; i<lowerPiles.size(); i++){
            list<Card> pile = lowerPiles[i];
            cout << "Pile " + std::to_string(i) + " Front->: ";
            for(list<Card>::iterator it=pile.begin(); it!=pile.end(); it++){
                cout << it->toStringOneLine()<<", ";
            }
            cout << " " << endl;
        }
    }
};

int main(){
    new Test();
    return 0;
}