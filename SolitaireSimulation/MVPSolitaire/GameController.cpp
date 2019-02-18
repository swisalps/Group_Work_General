#include "cardDeck.cpp"
#include <vector>
#include <stdlib.h>
#include <stack>
#include <set>
#include <iostream>
#include <array>
#include <string>
using namespace std;

class GameController

{
    public:
    cardDeck deck;
    int hasMovedFlip;
    int hasMovedLower;
    int failCounter;
    int visCtr;
    std::list<Card> shuffleDeck;
    std::list<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven, pile, temp;
    //lists below will be treated and interacted with as a stack. but are list becuase of the advanatages the list data structure offers in terms of moving sections of data
    std::list<Card> topDiamonds, topSpades, topHearts, topClubs, flipPile;
    std::array<list<Card>*, 7> lowerPiles;

    GameController()
    {

        initSolitaire();
        flipCard();
        checkFlip();
        checkLowerMove(7);

    }

    void initSolitaire()
    {
        deck = cardDeck();
        shuffleDeck = deck.shuffled;
        lowerOne = makePile(1);
        lowerTwo = makePile(2);
        lowerThree = makePile(3);
        lowerFour = makePile(4);
        lowerFive = makePile(5);
        lowerSix = makePile(6);
        lowerSeven = makePile(7);
        lowerPiles = {&lowerOne, &lowerTwo, &lowerThree, &lowerFour, &lowerFive, &lowerSix, &lowerSeven};
        failCounter = 0;

    }
    std::list<Card> makePile(int numCards){
        pile.clear();
        for(int i = 0; i < numCards; i++){
        pile.push_front(shuffleDeck.front());

        shuffleDeck.pop_front();
        }
        pile.front().setVis();
        cout << "pile number: " << numCards << " // top card: " << pile.front().toString() << endl;
        for(std::list<Card>::iterator it=pile.begin(); it != pile.end(); it++)
            std::cout << it->toString();
        return pile;

    }
    //method that checks what piles a flipcard can be placed on. if there is another card in flippile or a king, repeat process
    //@return true if the method empties the flip
    bool checkFlip(){
        //while(!flipPile.empty()){
        Card aCard = flipPile.front();
        int cNum = aCard.getNum();
        bool isRed = aCard.isRed();
        cout << "Flip Card: " << aCard.toString() << endl;
        if((lowerOne.front().isRed() != isRed) && (lowerOne.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerOne);
            flipPile.pop_front();
            hasMovedFlip++;
            cout << lowerOne.front().toString()<< endl;

        }
        else if((lowerTwo.front().isRed() != isRed) && (lowerTwo.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerTwo);
            hasMovedFlip++;
            cout << lowerTwo.front().toString()<< endl;

        }
        else if((lowerThree.front().isRed() != isRed) && (lowerThree.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerThree);
            hasMovedFlip++;
            cout << lowerThree.front().toString()<< endl;

        }
        else if((lowerFour.front().isRed() != isRed) && (lowerFour.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerFour);
            hasMovedFlip++;
            cout << lowerFour.front().toString()<< endl;

        }
        else if((lowerFive.front().isRed() != isRed) && (lowerFive.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerFive);
            hasMovedFlip++;
            cout << lowerFive.front().toString()<< endl;

        }
        else if((lowerSix.front().isRed() != isRed) && (lowerSix.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerSix);
            hasMovedFlip++;
            cout << lowerSix.front().toString()<< endl;

        }
        else if((lowerSeven.front().isRed() != isRed) && (lowerSeven.front().getNum() == cNum + 1)){
            moveCard(1, flipPile, lowerSeven);
            hasMovedFlip++;
            cout << lowerSeven.front().toString()<< endl;
        }
        else{
            return false;
        }

   // }
    if(hasMovedFlip != 0){
        return true;
    }
    return false;
    }

    // Checks one of the lower piles and finds the top visible card then sees if it can fit into any ace-spots
    // @return lowerPile the pile located on the lower part of the board (lowerOne, lowerTwo, etc...)
    // NOTE TO DEVELOPERS: After moving the card, I need to see if there is a non-vis card after it that I need to make visible, which I have yet to implement.
    //                     I don't know if we already made a method for this. I also have not yet included the hasMoved incrementing factor.
    //
    void lowerToAce(std::list<Card> lowerPile){
        if(!lowerPile.empty()){
            Card lowVisCard = lowerPile.front();
            if(lowVisCard.getNum() == 1){ // if the top card is an ace
                if(lowVisCard.getSuit() == "D"){
                    moveCard(1, lowerPile, topDiamonds);
                    cout << topDiamonds.front().toString()<< endl;
                }
                else if(lowVisCard.getSuit() == "S"){
                    moveCard(1, lowerPile, topSpades);
                    cout << topSpades.front().toString()<< endl;
                }
                else if(lowVisCard.getSuit() == "H"){
                    moveCard(1, lowerPile, topHearts);
                    cout << topHearts.front().toString()<< endl;
                }
                else{ // the suit of the lowVisCard is a Club
                    moveCard(1, lowerPile, topClubs);
                    cout << topClubs.front().toString()<< endl;
                }
            }
            else if(lowVisCard.getNum() > 1){ // if the top card is NOT and ace
                if(lowVisCard.getSuit() == "D"){
                    Card topCard = topDiamonds.front();
                    if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                        moveCard(1, lowerPile, topDiamonds);
                    }
                }
                else if(lowVisCard.getSuit() == "S"){
                    Card topCard = topSpades.front();
                    if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                        moveCard(1, lowerPile, topSpades);
                    }
                }
                else if(lowVisCard.getSuit() == "H"){
                    Card topCard = topHearts.front();
                    if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                        moveCard(1, lowerPile, topHearts);
                    }
                }
                else{ // the suit of the lowVisCard is a Club
                    Card topCard = topClubs.front();
                    if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                        moveCard(1, lowerPile, topClubs);
                    }
                }
            }
        }
    }



    bool checkLower()
    {
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
    bool checkLowerMove(int startingPile){
        list<Card>::iterator Itr;
        if(!(*lowerPiles[startingPile - 1]).empty()){
            Card lastVisOne = lastVisible(*lowerPiles[startingPile-1]);
            cout << "lastVis value: " <<lastVisOne.toString() << endl;
            Itr = (*lowerPiles[startingPile-1]).begin();
            temp.clear();
            for(int i = 0; i < 7; i++)
            {
                if(i != startingPile - 1)
                {
                    if(((*lowerPiles[i]).front().getNum() == lastVisOne.getNum()+1) && ((*lowerPiles[i]).front().isRed() != lastVisOne.isRed()))
                    {
                        for(int j = 0; j < visCtr; j++)
                        {
                            temp.splice(temp.begin(), *lowerPiles[startingPile -1], Itr);
                            cout << temp.back().toString() << endl;
                            Itr++;
                        }
                    moveCard(1, *lowerPiles[startingPile-1], *lowerPiles[i]);
                    //lowerPiles[i].splice(lowerPiles[i].begin(), temp);
                    std::string s = std::to_string(i+1);
                    cout << "lower" + s + " new front: " << (*lowerPiles[i]).front().toString() << endl;
                    return true;
                    }
                }
            }
        }
        else{
                //recursive call, doing this same process with lowerTwo at the top If
                //lowCtr = lowCtr + 1
                //checkLowerMove(lower)
                return false;
        }




        return false;
    }



/**moves a card from its current position to a new vector
@param numCards number of cards being moved
@param source location of card(s) that are going to be moved
@param dest destination for the cards being moved
*/

    void moveCard(int numCards, list<Card> source, list<Card> dest)
    {
        cout << "moveCard called" << endl;
        if (numCards == 1){  //If there is just one card it is moved to the destination pile and then it is remove from the source pile
            dest.push_front(source.front());
            cout << dest.front().toString() << endl;
        }
        else{ // If there is more than one card then the top card through numCards is spoliced from the source pile to the destination pile
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

        if(!shuffleDeck.empty())//If the deck is not empty the top card is pushed to the flippile and removed from the deck
        {
            flipPile.push_front(shuffleDeck.front());
            shuffleDeck.pop_front();
            flipPile.front().setVis();
        }
        else //If the deck is empty then the flip pile is swaped with the deck and reversevd
        {
            flipPile.swap(shuffleDeck);
            shuffleDeck.reverse();
            if ((hasMovedFlip == 0 ) && (hasMovedLower == 0)){ //Checks if a move has been done since the last time the deck was shuffled
                failCounter++;
                if (failCounter > 2){//If there was no moves then the fail counter is increased by one, if it reaches 3 the game is over
                    //TODO make game quit and result as loss
                }
            }
            else { //If a move has been done since the last shuffling then the hasMoved counters and fail counters are reset to 0
                hasMovedFlip = 0;
                hasMovedLower = 0;
                failCounter = 0;
            }
        }
    }

    Card lastVisible(std::list<Card> pile){
        visCtr = 0;
        list<Card>::iterator ItrVis;
        for(ItrVis=pile.begin(); ItrVis!=pile.end(); ++ItrVis){
            if(ItrVis->getVisible() == 0){
                visCtr = visCtr + 1;
            }
            else{
                return *ItrVis;
            }

        }
        return flipPile.front();
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