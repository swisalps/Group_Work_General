#include "Card.cpp"
#include "cardDeck.cpp"
#include <vector>
#include <stdlib.h>
#include <stack>

class GameController
{
    cardDeck c;
    std::vector<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven;
    std::stack<Card> topOne, topTwo, topThree, topFour, flipPile;

    GameController()
    {

    }

    void flipCard()
    {

    }

    int main()
    {
        return 0;
    }

};