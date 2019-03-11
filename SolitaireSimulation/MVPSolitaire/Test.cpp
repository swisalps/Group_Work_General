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
        
    }

    void init(){
        // Create a Shuffled Deck
        cardDeck shuffDeck = cardDeck();
        deck = shuffDeck.shuffled;
    }

    // ============ TESTS ============
    void test_getNum(){

    }
};