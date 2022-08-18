#include "card.h"
#include <random>
#include <algorithm>

class cardSet{
    private:
        card list[150];
        card discard = card(-3);
    
    public:
        cardSet(){
            //empty for now    
        };

        void createAndRandomize(){
            //create, then randomize the set of cards.
            //the set has 10 cards of each value from -2 to 12, except -2 which has 5 cards and 0 which has 15.
            for (int i=0;i<140;i+=14){ //10 cards of each, except -2
                list[i].setValue(-1);
                list[i+1].setValue(0);
                list[i+2].setValue(1);
                list[i+3].setValue(2);
                list[i+4].setValue(3);
                list[i+5].setValue(4);
                list[i+6].setValue(5);
                list[i+7].setValue(6);
                list[i+8].setValue(7);
                list[i+9].setValue(8);
                list[i+10].setValue(9);
                list[i+11].setValue(10);
                list[i+12].setValue(11);
                list[i+13].setValue(12);
            }
            for (int i = 0; i < 10; i+=2){ //5 cards of -2 and 5 additional cards of 0
                list[140+i].setValue(0);
                list[140+i+1].setValue(-2);
            }
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(&list[0], &list[150], g); //shuffle the set
        }

        card topCard(){
            for (int i = 0; i < 150; i++){
                if (list[i].getValue() != -3){
                    return list[i];
                }
            }
            //exit(EXIT_FAILURE);
        }

        card getCard(int index){
            return list[index];
        }

        void discardCard(card* card){
            discard.setValue(card->getValue());
        }

        card *getDiscard(){
            return &discard;
        }
};