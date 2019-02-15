#include <stdlib.h>     /* srand, rand */
#include <iostream>


class Card {
public:
int num;
std::string suit;
bool isVis;
//constructs a card instance made up of the cards number,
//suit and whether its value is visible to the user or not
    Card(int number, std::string cardSuit, bool visible){
        num = number;
        suit = cardSuit;
        isVis = visible;
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

     std::string toString(){
         std::string temp = "";
         return  std::to_string(num) + suit + std::to_string(isVis) + "\n" ;
     }
};


