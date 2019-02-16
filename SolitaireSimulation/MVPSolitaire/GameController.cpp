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
    int hasMovedFlip;
    int hasMovedLower;
    int failCounter;
    std::list<Card> shuffleDeck;
    std::list<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven;
    //lists below will be treated and interacted with as a stack. but are list becuase of the advanatages the list data structure offers in terms of moving sections of data
    std::list<Card> topOne, topTwo, topThree, topFour, flipPile;

    GameController()
    {

        initSolitaire();


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
        failCounter = 0;

    }
    void makePile(int numCards, std::list<Card> pile){

        for(int i = 0; i < numCards; i++){
        pile.push_front(shuffleDeck.front());

        shuffleDeck.pop_front();
        }
        pile.front().setVis();
        //for(std::list<Card>::iterator it=pile.begin(); it != pile.end(); it++)
          //  std::cout <<  it->toString();

    }
    //method that checks what piles a flipcard can be placed on. if their is another card in flippile or a king, repeat process
    //@return true if the method empties the flip
    bool checkFlip(){
        while(!flipPile.empty()){
        Card aCard = flipPile.front();
        int cNum = aCard.getNum();
        bool isRed = aCard.isRed();
        if(lowerOne.front().isRed() != isRed && lowerOne.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerOne);
            hasMovedFlip++;

        }
        else if(lowerTwo.front().isRed() != isRed && lowerTwo.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerTwo);
            hasMovedFlip++;

        }
        else if(lowerThree.front().isRed() != isRed && lowerThree.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerThree);
            hasMovedFlip++;

        }
        else if(lowerFour.front().isRed() != isRed && lowerFour.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerFour);
            hasMovedFlip++;

        }
        else if(lowerFive.front().isRed() != isRed && lowerFive.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerFive);
            hasMovedFlip++;

        }
        else if(lowerSix.front().isRed() != isRed && lowerSix.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerSix);
            hasMovedFlip++;

        }
        else if(lowerSeven.front().isRed() != isRed && lowerSeven.front().getNum() == cNum + 1){
            moveCard(1, flipPile, lowerSeven);
            hasMovedFlip++;
        }
        else{
            return false;
        }

    }
    if(hasMovedFlip != 0){
        return true;
    }
    }

    bool checkLower(bool move){
        //Check if you can move a card from the lower pile you are looking at to the ace-piles
        //Check if there is an invisible card you can make visible
        //If you moved, increment the hasMovedLower

        //Check if a whole deck can be moved (use splice method if there are invisible cards underneath pile)
        //Check if there is an invisible card you can make visible
        //If you moved, increment the hasMovedLower

        //Check if you can move a card from one pile to another pile
        //Check if there is an invisible card you can make visible
        //Check if the card you are moving is a king card
            //Check if there are any open/empty spaces for the king card
        //If you moved, increment the hasMovedLower

        //Check if you made a move
        //Yes: recurse; set bool to true
        //No: return; set bool to false


        return true;
    }



/**moves a card from its current position to a new vector
@param numCards number of cards being moved
@param source location of card(s) that are going to be moved
@param dest destination for the cards being moved
*/

    void moveCard(int numCards, list<Card> source, list<Card> dest)
    {
        if (numCards == 1){
            dest.push_front(source.front());
        }
        else{
            std::list<Card>::iterator it;
            it = source.begin();
            advance(it, numCards);
            dest.splice(source.begin(), source, it);
        }
       
        if(!source.front().getVisible())
            source.front().setVis();
    }
//flips a card from the shuffled deck to the flip pile.
    void flipCard()
    {

        if(!shuffleDeck.empty())
        {
            flipPile.push_front(shuffleDeck.front());
            shuffleDeck.pop_front();
            flipPile.front().setVis();
        }
        else
        {
            flipPile.swap(shuffleDeck);
            shuffleDeck.reverse();
            if ((hasMovedFlip == 0 ) && (hasMovedLower == 0)){
                failCounter++;
                if (failCounter > 2){
                    //TODO make game quit and result as loss
                }
            }
            else {
                hasMovedFlip = 0;
                hasMovedLower = 0;
                failCounter = 0;
            }
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