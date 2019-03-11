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
    cardDeck deck; // this deck is shuffled

    Test(){

    }

    void init(){
        // Create a Shuffled Deck
        deck = cardDeck();
    }

    // ============ TESTS ============
};