#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <list>
#include "Card.cpp"


class cardDeck {
    public:
std::list<Card> unShuffle;
std::list<Card> shuffled;

//constructs a card instance made up of the cards number,
//suit and whether its value is visible to the user or not
    cardDeck(){
        num = number;
        suit = cardSuit;
        isVis = visible;
    }
    void makeDiamond(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(new Card(i, "D", false));
       }
   }
   void makeSpade(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(new Card(i, "S", false));
       }
   }
   void makeHeart(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(new Card(i, "H", false));
       }
   }
   void makeClub(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(new Card(i, "C", false));
       }
   }
};


