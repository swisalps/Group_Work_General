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
    std::list<Card> pile, temp;
    //lists below will be treated and interacted with as a stack. but are list because of the advantages the list data structure offers in terms of moving sections of data
    std::list<Card> topDiamonds, topSpades, topHearts, topClubs, flipPile;
    std::array<std::list<Card>, 7> lowerPiles;

    //constructor for the GameController object: creates and runs the solitaire deck
    GameController()
    {
        //int n = 0;
        //int winCtr = 0;
        //double winP = 0.0;
        //while(n < 50){
            auto start = std::chrono::high_resolution_clock::now();
            //int ctr = 0;
            initSolitaire();
            //int winlose = run();
            run();
            //if(winlose==1){
                //winCtr++;
            //}
            //n++;
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
            cout<<"Execution Time: "<<duration.count()<<" microseconds\n";
        //}
        //winP = winCtr/n;
        //cout << "win Percentage after " << n << ": " << winP << endl;
    }
    //initializes the solitaire game
    void initSolitaire()
    {
        //To play using rigged deck set deck equal to cardDeck(0) for a pasing deck
        deck = cardDeck();//stacked deck
        shuffleDeck = deck.shuffled;
        visCtr = 0;
        hasMovedLower = 0;
        hasMovedFlip = 0;
	for(int i = 0; i < 7; i++)
	{
		lowerPiles[i] = makePile(i+1);
	}

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
        //cout << "Pile " + std::to_string(numCards) + " Front->: ";
        for(std::list<Card>::iterator it=pile.begin(); it != pile.end(); it++)
        {
            //std::cout << it->toStringOneLine() << ", ";
        }
        //cout << " " << endl;
        return pile;

    }

    //displays the piles
    void displayPiles(){
        for(int i = 0; i < 7; i++)
        {
            cout << "Pile " << i + 1 << " Size = " << lowerPiles[i].size() << " Front->: ";
            if(!lowerPiles[i].empty())
            {
                for(std::list<Card>::iterator it = lowerPiles[i].begin(); it != lowerPiles[i].end(); it++)
                {
                    std::cout << it->toStringOneLine() << ", ";
                }
            }
            else
            {
                cout << "Empty";
            }
            cout << " " << endl;
        }
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
    //also will recursively call itself until the flipPile is empty or it went through an entire call without making a move, finishing by fliping a new card from the deck to the flip pile
    //@return boolean
    bool checkFlip()
    {
        int moveMade = 0;
        if(!flipPile.empty()){
        Card aCard = flipPile.front();
        int cNum = aCard.getNum();
        bool isRed = aCard.isRed();
        bool hmm;
        //cout<<"Deck Top: "<<shuffleDeck.front().toString();
        //cout << "Flip Card: " << aCard.toString() << endl;
        //cout << "Flip Deck size: " << flipPile.size() << endl;
        if(cNum == 1){
            lowerToAceFirst(flipPile);
        }
        if(cNum == 13){
            if((!topDiamonds.empty()) && (aCard.getSuit() == "D") && (topDiamonds.front().getNum() == 12)){
                moveCard(1, flipPile, topDiamonds);
                hasMovedFlip++;
                moveMade++;

            }
            else if((!topHearts.empty()) && (aCard.getSuit() == "H") && (topHearts.front().getNum() == 12)){
                moveCard(1, flipPile, topHearts);
                hasMovedFlip++;
                moveMade++;
            }
            else if((!topSpades.empty()) && (aCard.getSuit() == "S") && (topSpades.front().getNum() == 12)){
                moveCard(1, flipPile, topSpades);
                hasMovedFlip++;
                moveMade++;
            }
            else if((!topClubs.empty()) && (aCard.getSuit() == "C") && (topClubs.front().getNum() == 12)){
                moveCard(1, flipPile, topClubs);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[0].empty()){
                moveCard(1, flipPile, lowerPiles[0]);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[1].empty()){
                moveCard(1, flipPile, lowerPiles[1]);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[2].empty()){
                moveCard(1, flipPile, lowerPiles[2]);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[3].empty()){
                moveCard(1, flipPile, lowerPiles[3]);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[4].empty()){
                moveCard(1, flipPile, lowerPiles[4]);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[5].empty()){
                moveCard(1, flipPile, lowerPiles[5]);
                hasMovedFlip++;
                moveMade++;
            }
            else if(lowerPiles[6].empty()){
                moveCard(1, flipPile, lowerPiles[6]);
                hasMovedFlip++;
                moveMade++;
            }

            else{
                //cout << "no open spaces for king " << endl;
            }

        }

        else if ((!lowerPiles[0].empty()) && (lowerPiles[0].front().isRed() != isRed) && (lowerPiles[0].front().getNum() == cNum + 1) && (lowerPiles[0].front().getNum() != 2)){
            //cout << "test12" << endl;
            moveCard(1, flipPile, lowerPiles[0]);
            hasMovedFlip++;
            moveMade++;
        }
        //cout << "test13" << endl;
		else if ((!lowerPiles[1].empty()) && (lowerPiles[1].front().isRed() != isRed) && (lowerPiles[1].front().getNum() == cNum + 1) && (lowerPiles[1].front().getNum() != 2)){
            //cout << "test13" << endl;
            moveCard(1, flipPile, lowerPiles[1]);
            hasMovedFlip++;
            moveMade++;
        }
        //cout << "test14" << endl;
		else if ((!lowerPiles[2].empty()) && (lowerPiles[2].front().isRed() != isRed) && (lowerPiles[2].front().getNum() == cNum + 1) && (lowerPiles[2].front().getNum() != 2)){
            //cout << "test14" << endl;
            moveCard(1, flipPile, lowerPiles[2]);
            hasMovedFlip++;
            moveMade++;
        }
        //cout << "test15" << endl;
		else if ((!lowerPiles[3].empty()) && (lowerPiles[3].front().isRed() != isRed) && (lowerPiles[3].front().getNum() == cNum + 1) && (lowerPiles[3].front().getNum() != 2)){
            //cout << "test15" << endl;
            moveCard(1, flipPile, lowerPiles[3]);
            hasMovedFlip++;
            moveMade++;
        }
        //cout << "test16" << endl;
		else if ((!lowerPiles[4].empty()) && (lowerPiles[4].front().isRed() != isRed) && (lowerPiles[4].front().getNum() == cNum + 1) && (lowerPiles[4].front().getNum() != 2)){
            //cout << "test16" << endl;
            moveCard(1, flipPile, lowerPiles[4]);
            hasMovedFlip++;
            moveMade++;
        }
        //cout << "test17" << endl;
		else if ((!lowerPiles[5].empty()) && (lowerPiles[5].front().isRed() != isRed) && (lowerPiles[5].front().getNum() == cNum + 1) && (lowerPiles[5].front().getNum() != 2)){
            //cout << "test17" << endl;
            moveCard(1, flipPile, lowerPiles[5]);
            hasMovedFlip++;
            moveMade++;

        }
        //cout << "test18" << endl;
		else if ((!lowerPiles[6].empty()) && (lowerPiles[6].front().isRed() != isRed) && (lowerPiles[6].front().getNum() == cNum + 1) && (lowerPiles[6].front().getNum() != 2)){
            //cout << "test18" << endl;
            moveCard(1, flipPile, lowerPiles[6]);
            hasMovedFlip++;
            moveMade++;
        }
        else if( (!topHearts.empty()) && (topHearts.front().getNum() == cNum - 1) && (aCard.getSuit() == "H")){
            //cout << "test19" << endl;
            moveCard(1, flipPile, topHearts);
            hasMovedFlip++;
            moveMade++;
        }
        else if((!topDiamonds.empty()) && (topDiamonds.front().getNum() == cNum - 1) && (aCard.getSuit() == "D")){
            //cout << "test20" << endl;
            moveCard(1, flipPile, topDiamonds);
            hasMovedFlip++;
            moveMade++;
        }
        else if((!topClubs.empty()) && (topClubs.front().getNum() == cNum - 1) && (aCard.getSuit() == "C")){
            //cout << "test21" << endl;
            moveCard(1, flipPile, topClubs);
            hasMovedFlip++;
            moveMade++;
        }
        else if((!topSpades.empty()) && (topSpades.front().getNum() == cNum - 1) && (aCard.getSuit() == "S")){
            //cout << "test22" << endl;
            moveCard(1, flipPile, topSpades);
            hasMovedFlip++;
            moveMade++;
        }

    }
    //cout << "MoveMade Value: " << moveMade << endl;
    if((moveMade > 0)){
        checkFlip();
        }
    else{
    flipCard();
    return false;
    }
    return false;
    }

    // Checks one of the lower piles and finds the top visible card then sees if it can fit into any ace-spots
    // @return lowerPile the pile located on the lower part of the board (lowerPiles[0], lowerPiles[1], etc...)
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
                    hasMovedLower++;
                    diamondA = true;
                    return 1;
                }
                else if(lowVisCard.getSuit() == "S"){
                    moveCard(1, lowerPile, topSpades);
                    hasMovedLower++;
                    spadeA = true;
                    return 1;
                }
                else if(lowVisCard.getSuit() == "H"){
                    moveCard(1, lowerPile, topHearts);
                    hasMovedLower++;
                    heartA = true;
                    return 1;
                }
                else{ // the suit of the lowVisCard is a Club
                    moveCard(1, lowerPile, topClubs);
                    hasMovedLower++;
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
                    //cout << "test25" << endl;
                    moveCard(1, lowerPile, topDiamonds);
                    hasMovedLower++;
                    return true;
                }
            }
            else if((lowVisCard.getSuit() == "S") && (!topSpades.empty())){
                Card topCard = topSpades.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                    //cout << "test26" << endl;
                     moveCard(1, lowerPile, topSpades);
                     hasMovedLower++;
                     return true;
                }
            }
            else if((lowVisCard.getSuit() == "H") && (!topHearts.empty())){
                Card topCard = topHearts.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){ // if the top card of the ace pile has a number that is less than the number of the low card by 1
                    //cout << "test27" << endl;
                    moveCard(1, lowerPile, topHearts);
                    hasMovedLower++;
                    return true;
                }
            }
            else if((lowVisCard.getSuit() == "C") && (!topClubs.empty())){ // the suit of the lowVisCard is a Club
                Card topCard = topClubs.front();
                if(topCard.getNum() == lowVisCard.getNum() - 1){// if the top card of the ace pile has a number that is less than the number of the low card by 1
                    //cout << "test28" << endl;
                    moveCard(1, lowerPile, topClubs);
                    hasMovedLower++;
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
            if(!lowerPiles[0].empty()){ // check the 1st pile for a king
                if (lowerPiles[0].front().getNum() == 13){
                    moveCard(1, lowerPiles[0], lowerPile);
                    hasMovedLower++;
                    return true;
                }
            }
            else if(!lowerPiles[1].empty()){// check the 2nd pile for a king
                if (lowerPiles[1].front().getNum() == 13){
                    moveCard(1, lowerPiles[1], lowerPile);
                    hasMovedLower++;
                    return true;
                }
            }
            else if(!lowerPiles[2].empty()){
                if (lowerPiles[2].front().getNum() == 13){
                    moveCard(1, lowerPiles[2], lowerPile);
                    hasMovedLower++;
                    return true;
                }
            }
            else if(!lowerPiles[3].empty()){
                if (lowerPiles[3].front().getNum() == 13){
                    moveCard(1, lowerPiles[3], lowerPile);
                    hasMovedLower++;
                    return true;
                }
            }
            else if(!lowerPiles[4].empty()){
                if (lowerPiles[4].front().getNum() == 13){
                    moveCard(1, lowerPiles[4], lowerPile);
                    hasMovedLower++;
                    return true;
                }
            }
            else if(!lowerPiles[5].empty()){
                if (lowerPiles[5].front().getNum() == 13){
                    moveCard(1, lowerPiles[5], lowerPile);
                    hasMovedLower++;
                    return true;
                }
            }
            else if(!lowerPiles[6].empty()){
                if (lowerPiles[6].front().getNum() == 13){
                    moveCard(1, lowerPiles[6], lowerPile);
                    hasMovedLower++;
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


    // this method checks if there are any non-visible cards left in the pile
    // this method uses the getCard method as well
    // this method is useful to find if the entire pile can be moved without worrying if there are any non-visible cards we need to splice
    // @param myPile the pile you want to find if it has a non-visible card in it
    // @return true the pile has a non-visible card in it
    // @return false the pile does not have a non-visible card in it; only visible cards
    bool findNonVis(std::list<Card> myPile){
        std::list<Card>::iterator itNon = myPile.begin();
        if(myPile.empty() == true)
        {
            //cout << "empty pile" << endl;
            return false;
        }
        else if(myPile.size() == 1)
        {
            //cout << "one card, no invisible" << endl;
            return false;
        }
         for(itNon=myPile.begin(); itNon!=myPile.end(); ++itNon){
            if(itNon->getVisible() == false){
                //cout << "nonVis return "<< itNon->toString() << endl;
                return true;
            }
            else{

            }
        }
        return false;
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
        //cout << "recursion: " << startingPile << endl;
        int n = 0;
        if(startingPile >= 0)
        {

            std::list<Card>::iterator Itr;
            if(!(lowerPiles[startingPile]).empty())
            {
                //cout << "before" << endl;
                Card lastVisOne = lastVisible(lowerPiles[startingPile]);
                //cout << "after" << endl;
                 if((lastVisOne.getNum() == 13) && (findNonVis(lowerPiles[startingPile]) == true)){
                    for(int j=0; j<=6; j++){
                        if(j != startingPile){ // make sure we move the pile to a different pile; think of pileNumber as the currentPile; skips over the pile we want to moveCard
                            if(lowerPiles[j].empty()){ // make sure the otherPile is empty
                                moveCard(visCtr, lowerPiles[startingPile], lowerPiles[j]);
                                hasMovedLower++;
                                //cout << "found move! " << endl;
                                return true;
                            }
                        }

                    }
                }
                else{
                Itr = lowerPiles[startingPile].begin();
                for(int i = 0; i < 7; i++)
                {
                    if((i != startingPile) && (!lowerPiles[i].empty()))
                    {
                        if((lowerPiles[i].front().getNum() == lastVisOne.getNum()+1) && (lowerPiles[i].front().isRed() != lastVisOne.isRed()))
                        {

                            moveCard(visCtr, lowerPiles[startingPile], lowerPiles[i]);
                            hasMovedLower++;
                            //cout << "lower " << i << " new front: " << lowerPiles[i].front().toString() << endl;
                            return true;
                        }

                    }
                }
                }
            }
            else
            {
                return checkLowerMove(startingPile - 1);
            }
            return checkLowerMove(startingPile - 1);
        }
        return false;
    }

/**moves a card from its current position to a new vector
@param numCards number of cards being moved
@param source location of card(s) that are going to be moved
@param dest destination for the cards being moved
*/

    void moveCard(int numCards, std::list<Card>& source, std::list<Card>& dest)
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
            //cout << "Source size before spice: " << source.size() << endl;
            //cout << "Dest size before spice: " << dest.size() << endl;
            dest.splice(dest.begin(), source, source.begin(), it);
            //cout << "Source size after spice: " << source.size() << endl;
            //cout << "Dest size after spice: " << dest.size() << endl;

        }
        if (!source.empty()){
			if (!source.front().getVisible())
				source.front().setVis();
		}
    }


//flips a card from the shuffled deck to the flip pile.
    void flipCard()
    {
        if(shuffleDeck.size() > 0)//If the deck is not empty the top card is pushed to the flippile and removed from the deck
        {
            flipPile.push_front(shuffleDeck.front());
            shuffleDeck.pop_front();
            flipPile.front().setVis();
        }
        else //If the deck is empty then the flip pile is swaped with the deck and reversevd
        {
            shuffleDeck.swap(flipPile);
            shuffleDeck.reverse();
            //cout << "flipPile becomes deck: "; //testing to make sure the flipPile is correctly reassembled to into the deck once the deck is emptied
            for(std::list<Card>::iterator it=shuffleDeck.begin(); it != shuffleDeck.end(); it++)
        {
            //cout << it->toStringOneLine() << ", ";
        }
            //cout << "\n";
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
            }//test
        }
    }
    //lastVisible method is an integral part of the checklowermove(). It returns the last visible card in a pile and also keeps track of the amount of cards ahead of the last visible card
    // through the visCtr variable. this is important becuase when executing a moveCard() call, you must provide the amount of cards to move, from the front to amount of cards deep in the pile
    //@param the ppile to find the last visible card for
    //@returns a Card object that is the last visible for the pile. (visCtr although it is not returned is just as important as the return itself)

    Card lastVisible(std::list<Card> ppile){
        visCtr = 0;
        std::list<Card>::iterator ItrVis = ppile.begin();
        //cout << "size of pile: " << ppile.size() << endl;
        if((ppile.size() > 1) && (findNonVis(ppile) == true)){
            for(ItrVis=ppile.begin(); ItrVis!=ppile.end(); ++ItrVis){
                if((ItrVis->getVisible() == 1) && (visCtr != ppile.size())){
                    visCtr++;
                }
                else{
                    ItrVis--;
                    return *ItrVis;
                }

            }
        }
        else{
            if(ppile.size() == 1){
                visCtr++;
                return ppile.back();
            }
            else if((ppile.size() > 1) && (findNonVis(ppile) == false)){
                for(ItrVis=ppile.begin(); ItrVis != ppile.end(); ++ItrVis){
                    visCtr++;
                    }
                    //cout << "test: " << ppile.back().toString() << endl;
                return ppile.back();
            }

        }
        // non-reachable statement; only reaches here if the pile size is 1 and findNonVis == false
        return ppile.back();
    }

//runs the GameController class
    int run()
    {
            int ctr = 0;
            flipCard();
        while((!gameWon)&&(!gameLost))
       {
           //cout << "---------NEW TURN BEGUN----------" << endl;
            //As long as the game is not won or lost the loop will continue
      //while(test < 20){
            ctr++;
            bool b = false;
            checkFlip();
            //cout << "checkFlip() completed " << endl;
            b = checkLowerMove(6);
            while(b){
                b = checkLowerMove(6);
            }

            lowerToAceFirst(lowerPiles[0]);//trys to place the front lowerPiles[0] card if its an ace onto the ace piles
            lowerToAceFirst(lowerPiles[1]);
            lowerToAceFirst(lowerPiles[2]);
            lowerToAceFirst(lowerPiles[3]);
            lowerToAceFirst(lowerPiles[4]);
            lowerToAceFirst(lowerPiles[5]);
            lowerToAceFirst(lowerPiles[6]);

            if(diamondA || clubA || spadeA || heartA){ //if statement that checks to see if the any of the aces have been placed on the ace piles
                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            //cout << "test 2" << endl;
            lowerToAceFirst(lowerPiles[1]); //trys to place the front lowerPiles[1] card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){//if statement that checks to see if the any of the aces have been placed on the ace piles
                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            //cout << "test 3" << endl;
            lowerToAceFirst(lowerPiles[2]); //trys to place the front lowerPiles[2] card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){//if statement that checks to see if the any of the aces have been placed on the ace piles
                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            //cout << "test 4" << endl;
            lowerToAceFirst(lowerPiles[3]);//trys to place the front lowerPiles[3] card if its an ace onto the ace piles
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            //cout << "test 5" << endl;
            lowerToAceFirst(lowerPiles[4]);
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            //cout << "test 6" << endl;
            lowerToAceFirst(lowerPiles[5]);
            if(diamondA || clubA || spadeA || heartA){

                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            //cout << "test 7" << endl;
            lowerToAceFirst(lowerPiles[6]);
            if(diamondA || clubA || spadeA || heartA){
                lowerToAce(flipPile);
                lowerToAce(lowerPiles[0]);
                lowerToAce(lowerPiles[1]);
                lowerToAce(lowerPiles[2]);
                lowerToAce(lowerPiles[3]);
                lowerToAce(lowerPiles[4]);
                lowerToAce(lowerPiles[5]);
                lowerToAce(lowerPiles[6]);
            }
            test++;
            if((topDiamonds.size() == 13)&&(topHearts.size() == 13)&&(topClubs.size() == 13)&&(topSpades.size() == 13))
                gameWon = true;
            //displayPiles();
            //cout << ctr << endl;
    }

    cout<<"Ran through: "<<ctr<<" times"<<"\n";
    if(gameWon){
        cout<<"You Won!\n";
        return 1;
    }
    else{
        cout<<"You lost!\n";
        return 0;
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

        GameController* game = new GameController();
        delete game;
        return 0;
    }