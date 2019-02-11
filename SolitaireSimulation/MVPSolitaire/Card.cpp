#include <stdlib.h>     /* srand, rand */
#include <iostream>


class Card {
int num;
std::string suit;
bool isVis;
    Card(int number, std::string cardSuit){
        num = number;
        suit = cardSuit;
    }
    int getNum(){
        return num;
    }
     std::string getSuit(){
         return suit;
     }
     bool isRed(){
         if ((suit != "S") || (suit != "C")){
             return true;
         }

         else{
             return false;
         }
     }
     bool getVisible(){
         return isVis;
     }
     void setVis(){
         isVis = true;
     }
     void setNotVis(){
         isVis = false;
     }
    //Compares lower value card to higher
    //Must be called on lower value card
     bool compareCardLow(Card otherCard){
         if ((num = otherCard.getNum() + 1)&&(this->isRed() != otherCard.isRed())){
             return true;
         }
         else{
             return false;
         }
     }
}


