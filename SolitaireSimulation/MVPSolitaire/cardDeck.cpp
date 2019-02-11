#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <list>
#include "Card.cpp"
#include<random>


class cardDeck {
    public:
std::list<Card> unShuffle;
std::list<Card> shuffled;
int randomInt;

//constructs a card instance made up of the cards number,
//suit and whether its value is visible to the user or not
    cardDeck(){
        makeClub();
        makeDiamond();
        makeHeart();
        makeSpade();

        for(std::list<Card>::iterator it=unShuffle.begin(); it != unShuffle.end(); ++it)
            std::cout <<  it->toString();
    }
    void makeDiamond(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(i, "D", false);
       }
   }
   void makeSpade(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(i, "S", false);
       }
   }
   void makeHeart(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(i, "H", false);
       }
   }
   void makeClub(){
       for(int i= 1; i <= 13; i = i + 1){
           unShuffle.emplace_front(i, "C", false);
       }
   }
   std::list<Card> shuffleDeck(){
       for(int n = unShuffle.size() + 1; n > 0; n--){
           randomInt = rand()/RAND_MAX + (n + 1);
           Card temp = unShuffle.back();
           unShuffle.pop_back();
            }
   }
};
    int main(){
     new cardDeck();
     return 0;
 }
