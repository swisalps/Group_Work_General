#include "cardDeck.cpp"
#include <vector>
#include <stdlib.h>
#include <stack>
#include <set>
using namespace std;

class GameController
{
    cardDeck deck;
    std::set<Card> shuffleDeck;
    std::vector<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven;
    std::stack<Card> topOne, topTwo, topThree, topFour, flipPile;

    GameController()
    {

    }

    void initSolitaire()
    {
        //lowerOne.insert(0, )
    }

//moves a card from its current position to a new vector
    void moveCard(Card c, vector<Card> v)
    {
        v.emplace(v.end(), c);
    }

    void flipCard(Card c)
    {
        if(c.getVisible())
        {
            c.setNotVis();
        }
        else
        {
            c.setVis();
        }
    }

//runs the GameController class
    void run()
    {

    }

//terminates the program
    void stop()
    {
        return;
    }


    int main()
    {
        return 0;
    }

};