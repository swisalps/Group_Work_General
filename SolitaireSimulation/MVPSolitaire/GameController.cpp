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
    int test;
    int visCtr, lowOneInt, lowTwoInt, lowThreeInt, lowFourInt, lowFiveInt, lowSixInt, lowSevenInt;
    bool gameLost, gameWon, heartA, clubA, spadeA, diamondA, lowOne, lowTwo, lowThree, lowFour, lowFive, lowSix, lowSeven;
    std::list<Card> shuffleDeck;
    std::list<Card> lowerOne, lowerTwo, lowerThree, lowerFour, lowerFive, lowerSix, lowerSeven, pile, temp;
    //lists below will be treated and interacted with as a stack. but are list becuase of the advanatages the list data structure offers in terms of moving sections of data
    std::list<Card> topDiamonds, topSpades, topHearts, topClubs, flipPile;
    std::array<list<Card>*, 7> lowerPiles;

    //constructor for the GameController object: creates and runs the solitaire deck
    GameController()
    {
        int ctr = 0;
        initSolitaire();
        run();
    }
    //initalizes the solitaire game
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
        lowOne = false, lowTwo = false, lowThree = false, lowFour = false, lowFive = false, lowSix = false, lowSeven = false;
        gameLost = false, gameWon = false;
        spadeA = false, clubA = false, heartA = false, diamondA = false;
    }

    //makes each pile
    std::list<Card> makePile(int numCards){
        pile.clear();
        for(int i = 0; i < numCards; i++){
        pile.push_front(shuffleDeck.front());

        shuffleDeck.pop_front();
        }
        pile.front().setVis();
        cout << "Pile " + std::to_string(numCards) + " Front->: ";
        for(std::list<Card>::iterator it=pile.begin(); it != pile.end(); it++)
        {
            std::cout << it->toStringOneLine() << ", ";
        }
        cout << " " << endl;
        return pile;

    }

    //displays the piles
    void displayPiles(){
        cout << "Pile 1 Front->: ";
        for(std::list<Card>::iterator it=lowerOne.begin(); it != lowerOne.end(); it++)
            std::cout << it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Pile 2 Front->: ";
        for(std::list<Card>::iterator it=lowerTwo.begin(); it != lowerTwo.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Pile 3 Front->: ";
        for(std::list<Card>::iterator it=lowerThree.begin(); it != lowerThree.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Pile 4 Front->: ";
        for(std::list<Card>::iterator it=lowerFour.begin(); it != lowerFour.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Pile 5 Front->: ";
        for(std::list<Card>::iterator it=lowerFive.begin(); it != lowerFive.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Pile 6 Front->: ";
        for(std::list<Card>::iterator it=lowerSix.begin(); it != lowerSix.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Pile 7 Front->: ";
        for(std::list<Card>::iterator it=lowerSeven.begin(); it != lowerSeven.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Diamond Aces: ";
        for(std::list<Card>::iterator it=topDiamonds.begin(); it != topDiamonds.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Hearts Aces: ";
        for(std::list<Card>::iterator it=topHearts.begin(); it != topHearts.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Spades Aces: ";
        for(std::list<Card>::iterator it=topSpades.begin(); it != topSpades.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << " " << endl;
        cout << "Clubs Aces: ";
        for(std::list<Card>::iterator it=topClubs.begin(); it != topClubs.end(); it++)
            std::cout <<it->toStringOneLine() << ", ";
        cout << "" << endl;
        cout << "------------------------" << endl;

    }

    //method that checks what piles the most recent flip card can be placed on. First checks if the flip card is an ace, if so it places it on the ace proper ace pile
    //if not an ace, it then checks to see if the flip card was a king, if so, it checks to see if any of the lower piles are empty so the king can be placed
    //if the flip card is not an ace or a king, it will check all 7 lower piles and the 4 ace piles to see if the flip card can be placed at all
    //@return boolean
    bool checkFlip()
    {
        //while(!flipPile.empty()){
        Card aCard = flipPile.front();
        int cNum = aCard.getNum();
        bool isRed = aCard.isRed();
        bool hmm;
        cout << "Flip Card: " << aCard.toString() << endl;
        if(cNum == 1){
            lowerToAceFirst(flipPile);
        }
        if(cNum == 13){
            if(lowerOne.empty()){
                moveCard(1, flipPile, lowerOne);
                flipCard();
                hasMovedFlip++;
            }
            else if(lowerTwo.empty()){
                moveCard(1, flipPile, lowerTwo);
                flipCard();
                hasMovedFlip++;
            }
            else if(lowerThree.empty()){
                moveCard(1, flipPile, lowerThree);
                flipCard();
                hasMovedFlip++;
            }
            else if(lowerFour.empty()){
                moveCard(1, flipPile, lowerFour);
                flipCard();
                hasMovedFlip++;
            }
            else if(lowerFive.empty()){
                moveCard(1, flipPile, lowerFive);
                flipCard();
                hasMovedFlip++;
            }
            else if(lowerSix.empty()){
                moveCard(1, flipPile, lowerOne);
                flipCard();
                hasMovedFlip++;
            }
            else if(lowerSeven.empty()){
                moveCard(1, flipPile, lowerSeven);
                flipCard();
                hasMovedFlip++;
            }
            else{
                //cout << "no open spaces for king " << endl;
            }
        }
        else if((lowerOne.front().isRed() != isRed) && (lowerOne.front().getNum() == cNum + 1) && (lowerOne.front().getNum() != 2) && (!lowerOne.empty())){
            moveCard(1, flipPile, lowerOne);
            hasMovedFlip++;
            flipCard();
            //cout << lowerOne.front().toString()<< endl;
        }
        else if((lowerTwo.front().isRed() != isRed) && (lowerTwo.front().getNum() == cNum + 1) && (lowerTwo.front().getNum() != 2) && (!lowerTwo.empty())){
            moveCard(1, flipPile, lowerTwo);
            hasMovedFlip++;
            flipCard();
            //cout << lowerTwo.front().toString()<< endl;
        }
        else if((lowerThree.front().isRed() != isRed) && (lowerThree.front().getNum() == cNum + 1) && (lowerThree.front().getNum() != 2)){
            moveCard(1, flipPile, lowerThree);
            hasMovedFlip++;
            flipCard();
           //cout << lowerThree.front().toString()<< endl;

        }
        else if((lowerFour.front().isRed() != isRed) && (lowerFour.front().getNum() == cNum + 1) && (lowerFour.front().getNum() != 2)){
            moveCard(1, flipPile, lowerFour);
            hasMovedFlip++;
            flipCard();
            //cout << lowerFour.front().toString()<< endl;

        }
        else if((lowerFive.front().isRed() != isRed) && (lowerFive.front().getNum() == cNum + 1) && (lowerFive.front().getNum() != 2)){
            moveCard(1, flipPile, lowerFive);
            hasMovedFlip++;
            flipCard();
            //cout << lowerFive.front().toString()<< endl;

        }
        else if((lowerSix.front().isRed() != isRed) && (lowerSix.front().getNum() == cNum + 1) && (lowerSix.front().getNum() != 2)){
            moveCard(1, flipPile, lowerSix);
            hasMovedFlip++;
            flipCard();
            //cout << lowerSix.front().toString()<< endl;

        }
        else if((lowerSeven.front().isRed() != isRed) && (lowerSeven.front().getNum() == cNum + 1) && (lowerSeven.front().getNum() != 2)){
            moveCard(1, flipPile, lowerSeven);
            hasMovedFlip++;
            flipCard();
            //cout << lowerSeven.front().toString()<< endl;
        }
        else if((topHearts.front().getNum() == cNum + 1) && (aCard.getSuit() == "H")){
            moveCard(1, flipPile, topHearts);
            hasMovedFlip++;
            flipCard();
        }
        else if((topDiamonds.front().getNum() == cNum + 1) && (aCard.getSuit() == "D")){
            moveCard(1, flipPile, topDiamonds);
            hasMovedFlip++;
            flipCard();
        }
        else if((topClubs.front().getNum() == cNum + 1) && (aCard.getSuit() == "C")){
            moveCard(1, flipPile, topClubs);
            hasMovedFlip++;
            flipCard();
        }
        else if((topSpades.front().getNum() == cNum + 1) && (aCard.getSuit() == "S")){
            moveCard(1, flipPile, topSpades);
            hasMovedFlip++;
            flipCard();
        }
        else{
            flipCard();
        }
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
    //This method only looks  for aces that are on the front of any of the lower piles.
    //if it finds an ace it will immiediatly move it to its assoicated ace piles
    int lowerToAceFirst(std::list<Card>& lowerPile){
        if(!lowerPile.empty()){
            Card lowVisCard = lowerPile.front();
            if(lowVisCard.getNum() == 1){ // if the top card is an ace

                if(lowVisCard.getSuit() == "D"){
                    moveCard(1, lowerPile, topDiamonds);
                    diamondA = true;
                    return 1;
                }
                else if(lowVisCard.getSuit() == "S"){
                    moveCard(1, lowerPile, topSpades);
                    spadeA = true;
                    return 1;
                }
                else if(lowVisCard.getSuit() == "H"){
                    moveCard(1, lowerPile, topHearts);
                    heartA = true;
                    return 1;
                }
                else{ // the suit of the lowVisCard is a Club
                    moveCard(1, lowerPile, topClubs);
                    clubA = true;
                    return 1;
                }
            }

        return 0;
    }
    return 0;
    }
    //this is method is called only after an pile as the first ACE card. the ace must be placed
    // first before this method is called. this method will always see if any cards in the lower piles can be addded to the ace piles
    //@param: the lowerPile you want to see if its front card fits in any of the ace piles
    //@return: true if it moves a card from lowerPile to an ace spot, false if not
    bool lowerToAce(std::list<Card>& lowerPile){
        if(!lowerPile.empty()){
        Card lowVisCard = lowerPile.front();
            if((lowVisCard.getSuit() == "D") && (!topDiamonds.empty())){
                Card topCard = topDiamonds.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){// if the top card of the ace pile has a number that is less than the number of the low card by 1
                    moveCard(1, lowerPile, topDiamonds);
                    return true;
                }
            }
            else if((lowVisCard.getSuit() == "S") && (!topSpades.empty())){
                Card topCard = topSpades.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                     moveCard(1, lowerPile, topSpades);
                     return true;
                }
            }
            else if((lowVisCard.getSuit() == "H") && (!topHearts.empty())){
                Card topCard = topHearts.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                    moveCard(1, lowerPile, topHearts);
                    return true;
                }
            }
            else if((lowVisCard.getSuit() == "C") && (!topClubs.empty())){ // the suit of the lowVisCard is a Club
                Card topCard = topClubs.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){// if the top card of the ace pile has a number that is less than the number of the low card by 1
                    moveCard(1, lowerPile, topClubs);
                    return true;
                    }
                }
            else{
                return false;
            }
        }
            return false;
    }

    // moves a king card from a low pile to an empty low pile
    // @param lowerPile a pile you are looking at assumed to be empty
    bool lowKingtoEmpty(std::list<Card> lowerPile){
        if(lowerPile.empty()){ //if the pile you are looking at is empty
            // check all piles to find a king
            if(!lowerOne.empty()){ // check the 1st pile for a king
                if (lowerOne.front().getNum() == 13){
                    moveCard(1, lowerOne, lowerPile);
                    return true;
                }
            }
            else if(!lowerTwo.empty()){// check the 2nd pile for a king
                if (lowerTwo.front().getNum() == 13){
                    moveCard(1, lowerTwo, lowerPile);
                    return true;
                }
            }
            else if(!lowerThree.empty()){
                if (lowerThree.front().getNum() == 13){
                    moveCard(1, lowerThree, lowerPile);
                    return true;
                }
            }
            else if(!lowerFour.empty()){
                if (lowerFour.front().getNum() == 13){
                    moveCard(1, lowerFour, lowerPile);
                    return true;
                }
            }
            else if(!lowerFive.empty()){
                if (lowerFive.front().getNum() == 13){
                    moveCard(1, lowerFive, lowerPile);
                    return true;
                }
            }
            else if(!lowerSix.empty()){
                if (lowerSix.front().getNum() == 13){
                    moveCard(1, lowerSix, lowerPile);
                    return true;
                }
            }
            else if(!lowerSeven.empty()){
                if (lowerSeven.front().getNum() == 13){
                    moveCard(1, lowerSeven, lowerPile);
                    return true;
                }
            }
            else{
                return false;
            }
            return false;
        }
        return false;
    }


/*
This method is executed at the beginning of the gameController() method each time a new flip card is flipped. it sees if pile lowerOne has a size of 1.
if it does, it sees if it can move that card to any of the other lower piles in order to free up lowerOne so a king can be placed in the newly created
open pile spot. this method could become obsolete once checkLowerMove() is fully implemented.
@return bool: true if pile one is now open, false if not
*/
    bool freeUpFirstPile()
    {

        if(lowerOne.size() == 1){ //checks to see if lowerOne has only one card. if so the method will attempt to move it in order to free up the pile
            Card pOneCard = lowerOne.front();
            if((lowerTwo.front().isRed() != pOneCard.isRed()) && (lowerTwo.front().getNum() == pOneCard.getNum() + 1)){
                moveCard(1, lowerOne, lowerTwo);
        }
            else if((lowerThree.front().isRed() != pOneCard.isRed()) && (lowerThree.front().getNum() == pOneCard.getNum() + 1)){
                moveCard(1, lowerOne, lowerThree);
            }
            else if((lowerFour.front().isRed() != pOneCard.isRed()) && (lowerFour.front().getNum() == pOneCard.getNum() + 1)){
                moveCard(1, lowerOne, lowerFour);
            }
            else if((lowerFive.front().isRed() != pOneCard.isRed()) && (lowerFive.front().getNum() == pOneCard.getNum() + 1)){
                moveCard(1, lowerOne, lowerFive);
            }
            else if((lowerSix.front().isRed() != pOneCard.isRed()) && (lowerSix.front().getNum() == pOneCard.getNum() + 1)){
                moveCard(1, lowerOne, lowerSix);
            }
            else if((lowerSeven.front().isRed() != pOneCard.isRed()) && (lowerSeven.front().getNum() == pOneCard.getNum() + 1)){
                moveCard(1, lowerOne, lowerSeven);
            }
            else{
                return false;
            }
            return false;
        }


        return true;
    }

    // **** This method will be later incorporated into the checkLowerMethod() once finished. ****
    // **** MAYBE KEEP FOR TESTING PURPOSES? ***
    // This method will check a lower pile (pileNumber) and see if its ENTIRE group of visible cards
    // can be moved to another pile, or an empty pile if the pile we want to move will have a king in it.
    //@param pileNumber the number indicating which pile (1-7) we want to move
    //@return true the pile has been moved
    //@return false the pile we want to move is either empty, has only 1 card in it, or cannot find a valid pile to move into
    bool checkLowerMoveEntirePile(int pileNumber){
        //get the current pile to look at (ENCOMPASS INSIDE FOR LOOP???????)
        std::list<Card> currentPile = *lowerPiles[pileNumber-1]; // NOTE: lowerPiles indices count from 0-6 and pileNumber ranges between 1-7, so we need -1.
        //check to see if the pile is NOT empty.
        //check to see if the pile has more than one card in it.
        if((!currentPile.empty()) && (currentPile.size() > 1)){
                // look at the current pile's bottom-most visible card
                Card bottomMostVisCard = getCard(currentPile, 0); // place-holder
                int numOfVisCards = 0; // the number of cards we need to move
                for(int i=0; i<currentPile.size(); i++){
                    Card currentCard = getCard(currentPile, i);
                    if((currentCard.getVisible() == false) || (i == currentPile.size())){ // if you reach a non-vis card OR you reach past the end of the list (there are only visible cards in the pile)
                        // you found a non-vis card or reached past the end of the list, get the card before it which should be vis
                        bottomMostVisCard = getCard(currentPile, i-1);
                        break;
                    }
                    numOfVisCards++;
                }
                // check if the bottom-most visible card fits with a top card in one of the other piles
                // assume the bottomMostVisCard is a king
                if(bottomMostVisCard.getNum() == 13){
                    for(int i=1; i<=7; i++){
                        if(i!=pileNumber){ // make sure we move the pile to a different pile; think of pileNumber as the currentPile; skips over the pile we want to moveCard
                            std::list<Card> otherPile = *lowerPiles[i]; // the pile we are comparing the currentPile to
                            if(otherPile.empty()){ // make sure the otherPile is empty
                                moveCard(numOfVisCards, currentPile, otherPile);
                                return true;
                            }
                            //else look for another pile that could be empty
                        }
                    }
                }
                else{ // the bottomMostVisCard is NOT a king
                    for(int i=1; i<=7; i++){
                        if(i!=pileNumber){ // make sure we move the pile to a different pile; think of pileNumber as the currentPile; skips over the pile we want to move
                            std::list<Card> otherPile = *lowerPiles[i]; // the pile we are comparing the currentPile to
                            // compare the front/top card of the otherPile to the bottomMostVisCard of the currentPile
                            if(otherPile.front().getNum() == bottomMostVisCard.getNum() + 1 && //if the num of the other card is higher by 1...
                                otherPile.front().isRed() != bottomMostVisCard.isRed()){       //if the colors are not the same...
                                moveCard(numOfVisCards, currentPile, otherPile); // move the pile
                                return true;
                            }
                            // else look for another pile to compare the bottomMostVisCard to.
                        }
                    }
                }
                std::cout << "Fail: Cannot find a pile to move to.";
                return false; // we cannot find another pile to move to.
        }
        std::cout << "Fail: the pile we want to move is either empty or has only 1 card in it.";
        return false; // the pileNumber we used is either empty or only has only one card in it.
    }

    // this method checks if there are any non-visible cards left in the pile
    // this method uses the getCard method as well
    // this method is useful to find if the entire pile can be moved without worrying if there are any non-visible cards we need to splice
    // @param myPile the pile you want to find if it has a non-visible card in it
    // @return true the pile has a non-visible card in it
    // @return false the pile does not have a non-visible card in it; only visible cards
    bool findNonVis(list<Card> myPile){
        for(int i=0; i<myPile.size(); i++){
            Card myCard = getCard(myPile, i);
            if(myCard.getVisible() == false){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }

    // This method getCard() takes in the list you want to search and the index of that list
    // and finds the Card element in that list.
    Card getCard(list<Card> myList, int index){
        list<Card>::iterator it = myList.begin();
        for(int i=0; i<index; i++){
            ++it;
        }
        return *it;
    }

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
    bool checkLowerMove(int startingPile){
        if(startingPile >= 1)
        {
            list<Card>::iterator Itr;
            if(!(*lowerPiles[startingPile - 1]).empty()){
                Card lastVisOne = lastVisible(*lowerPiles[startingPile-1]);
                cout << "lastVis value: " <<lastVisOne.toString() << endl;
                Itr = (*lowerPiles[startingPile-1]).begin();
                temp.clear();
                int n = 0;
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
                if(n == 0)
                {
                    return checkLowerMove(startingPile - 1);
                }
            }
            else
            {
                return checkLowerMove(startingPile -1);
            }
        }
        else{
                return false;
        }
        return false;
    }



/**moves a card from its current position to a new vector
@param numCards number of cards being moved
@param source location of card(s) that are going to be moved
@param dest destination for the cards being moved
*/

    void moveCard(int numCards, list<Card>& source, list<Card>& dest)
    {
        //cout << "moveCard called " << endl;
        if (numCards == 1){  //If there is just one card it is moved to the destination pile and then it is remove from the source pile
            dest.push_front(source.front());
            source.pop_front();
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

        if(shuffleDeck.size() > 1)//If the deck is not empty the top card is pushed to the flippile and removed from the deck
        {
            flipPile.push_front(shuffleDeck.front());
            shuffleDeck.pop_front();
            flipPile.front().setVis();
        }
        else //If the deck is empty then the flip pile is swaped with the deck and reversevd
        {
            shuffleDeck.swap(flipPile);
            shuffleDeck.reverse();
            if ((hasMovedFlip == 0 ) && (hasMovedLower == 0)){ //Checks if a move has been done since the last time the deck was shuffled
                failCounter++;
                if (failCounter > 2){//If there was no moves then the fail counter is increased by one, if it reaches 3 the game is over
                    gameLost = true;
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
            if(ItrVis->getVisible() == 1){
                visCtr = visCtr + 1;
            }
            else{
                ItrVis--;
                return *ItrVis;
            }

        }
        return flipPile.front();
    }

//runs the GameController class
    void run()
    {
            int ctr = 0;
        //while((!gameWon)&&(!gameLost))
       // {
            //As long as the game is not won or lost the loop will continue
    while(test < 10){
            ctr++;
            flipCard();
            freeUpFirstPile(); //checks if lowerOne size = 1. if so attempts to move that one card to free up pile
            lowKingtoEmpty(lowerOne); //checks to see if lowerOne or lowerTwo are empty. if so will check the other 5 piles front card to see if they are kings
            lowKingtoEmpty(lowerTwo); // and can be moved to either of the potentially open piles
            checkFlip();
            lowerToAceFirst(lowerOne);//trys to place the front lowerOne card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){ //if statement that checks to see if the any of the aces have been placed on the ace piles
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            lowerToAceFirst(lowerTwo); //trys to place the front lowerTwo card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){//if statement that checks to see if the any of the aces have been placed on the ace piles
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            lowerToAceFirst(lowerThree); //trys to place the front lowerThree card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){//if statement that checks to see if the any of the aces have been placed on the ace piles
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            lowerToAceFirst(lowerFour);//trys to place the front lowerFour card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            lowerToAceFirst(lowerFive);
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            lowerToAceFirst(lowerSix);
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            lowerToAceFirst(lowerSeven);
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(lowerOne);
                lowerToAce(lowerTwo);
                lowerToAce(lowerThree);
                lowerToAce(lowerFour);
                lowerToAce(lowerFive);
                lowerToAce(lowerSix);
                lowerToAce(lowerSeven);
            }
            bool b = checkLowerMove(7);
            if(b == true)
            {

            }
            test++;
            if((topDiamonds.size() == 13)&&(topHearts.size() == 13)&&(topClubs.size() == 13)&&(topSpades.size() == 13))
                gameWon = true;
            displayPiles();
    }
    displayPiles();
    //cout<< "return values from ace trackers: D" << diamondA << ", H" << heartA << ", S" << spadeA << ", C" << clubA << endl;
    //cout<< "lower1 lastVis return: " << lastVisible(lowerOne).toString() << endl;
    //cout<< "lower2 lastVis return: " << lastVisible(lowerTwo).toString() << endl;
    //cout<< "lower3 lastVis return: " << lastVisible(lowerThree).toString() << endl;
    //cout<< "lower4 lastVis return: " << lastVisible(lowerFour).toString() << endl;
    //cout<< "lower5 lastVis return: " << lastVisible(lowerFive).toString() << endl;
    //cout<< "lower6 lastVis return: " << lastVisible(lowerSix).toString() << endl;
    //cout<< "lower7 lastVis return: " << lastVisible(lowerSeven).toString() << endl;
    cout<<"Ran through: "<<ctr<<" times"<<"\n";
    if(gameWon){
        cout<<"You Won!\n";
    }
    else{
        cout<<"You lost!\n";
    }
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