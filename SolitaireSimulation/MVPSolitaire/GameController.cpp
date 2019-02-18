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
    int visCtr;
    std::list<Card> shuffleDeck;
    std::list<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven, pile, temp;
    //lists below will be treated and interacted with as a stack. but are list becuase of the advanatages the list data structure offers in terms of moving sections of data
    std::list<Card> topDiamonds, topSpades, topHearts, topClubs, flipPile;

    GameController()
    {

        initSolitaire();
        flipCard();
        checkFlip();
        checkLowerMove();

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
                }
                else if(lowVisCard.getSuit() == "S"){
                    moveCard(1, lowerPile, topSpades);
                }
                else if(lowVisCard.getSuit() == "H"){
                    moveCard(1, lowerPile, topHearts);
                }
                else{ // the suit of the lowVisCard is a Club
                    moveCard(1, lowerPile, topClubs);
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
    bool checkLowerMove(){
        list<Card>::iterator Itr;
        if(!lowerSeven.empty()){
            Card lastVisOne = lastVisible(lowerSeven);
            cout << "lastVis value: " <<lastVisOne.toString() << endl;
            Itr = lowerSeven.begin();
            temp.clear();
            if((lowerTwo.front().getNum() == lastVisOne.getNum()+1) && (lowerTwo.front().isRed() != lastVisOne.isRed())){
                for(int i=0; i < visCtr; i++){
                temp.splice(temp.begin(), lowerSeven, Itr);
                cout << temp.back().toString() << endl;
                Itr++;
            }
                lowerTwo.splice(lowerTwo.begin(), temp);
                cout << "lowerTwo new front" << lowerTwo.front().toString() << endl;
                return true;
            }
            else if((lowerThree.front().getNum() == lastVisOne.getNum()+1) && (lowerThree.front().isRed() != lastVisOne.isRed())){
                for(int i=0; i < visCtr; i++){
                temp.splice(temp.begin(), lowerSeven, Itr);
                cout << temp.back().toString() << endl;
                Itr++;
            }
                lowerThree.splice(lowerThree.begin(), temp);
                cout << "lowerThree new front" << lowerThree.front().toString() << endl;
                return true;
            }
            else if((lowerFour.front().getNum() == lastVisOne.getNum()+1) && (lowerFour.front().isRed() != lastVisOne.isRed())){
                for(int i=0; i < visCtr; i++){
                temp.splice(temp.begin(), lowerSeven, Itr);
                cout << temp.back().toString() << endl;
                Itr++;
            }
                lowerFour.splice(lowerFour.begin(), temp);
                cout << "lowerFour new front" << lowerFour.front().toString() << endl;
                return true;
            }
            else if((lowerFive.front().getNum() == lastVisOne.getNum()+1) && (lowerFive.front().isRed() != lastVisOne.isRed())){
                for(int i=0; i < visCtr; i++){
                temp.splice(temp.begin(), lowerSeven, Itr);
                cout << temp.back().toString() << endl;
                Itr++;
            }
                lowerFive.splice(lowerFive.begin(), temp);
                cout << "lowerFive new front" << lowerFive.front().toString() << endl;
                return true;
            }
            else if((lowerSix.front().getNum() == lastVisOne.getNum()+1) && (lowerSix.front().isRed() != lastVisOne.isRed())){
                for(int i=0; i < visCtr; i++){
                temp.splice(temp.begin(), lowerSeven, Itr);
                cout << temp.back().toString() << endl;
                Itr++;
            }
                lowerSix.splice(lowerSix.begin(), temp);
                cout << "lowerSix new front" << lowerSix.front().toString() << endl;
                return true;
            }
            else if((lowerOne.front().getNum() == lastVisOne.getNum()+1) && (lowerOne.front().isRed() != lastVisOne.isRed())){
                for(int i=0; i < visCtr; i++){
                temp.splice(temp.begin(), lowerSeven, Itr);
                cout << temp.back().toString() << endl;
                Itr++;
            }
                lowerOne.splice(lowerOne.begin(), temp);
                cout << "lowerOne new front" << lowerOne.front().toString() << endl;
                return true;
            }
            else{
                //recursive call, doing this same process with lowerTwo at the top If
                //lowCtr = lowCtr + 1
                //checkLowerMove(lower)
                return false;
            }



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
        if (numCards == 1){
            dest.push_front(source.front());
            cout << dest.front().toString() << endl;
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