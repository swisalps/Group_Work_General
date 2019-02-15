#include "cardDeck.cpp"
#include <vector>
#include <stdlib.h>
#include <stack>
#include <set>
#include <iostream>
using namespace std;

class GameController

{
    public:
    cardDeck deck;
    std::list<Card> shuffleDeck;
    std::list<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven;
    std::stack<Card> topOne, topTwo, topThree, topFour, flipPile;

    GameController()
    {

        initSolitaire();
for(std::list<Card>::iterator it=lowerSeven.begin(); it != lowerSeven.end(); ++it)
            std::cout <<  it->toString();

    }

    void initSolitaire()
    {
        deck = cardDeck();
        shuffleDeck = deck.shuffled;
        makePile(1,lowerOne);
        makePile(2,lowerTwo);
        makePile(3,lowerThree);
        makePile(4,lowerFour);
        makePile(5,lowerFive);
        makePile(6,lowerSix);
        makePile(7,lowerSeven);

    }
    void makePile(int numCards, std::list<Card> pile){

        for(int i = 0; i < numCards; i++){
        pile.push_front(shuffleDeck.front());

        shuffleDeck.pop_front();
        }
        pile.front().setVis();
        std::cout<<pile.front().toString();
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




};
int main()
    {
        new GameController();
        return 0;
    }