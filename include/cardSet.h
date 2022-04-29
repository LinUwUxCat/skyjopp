#include "card.h"
#include <random>
#include <algorithm>

class cardSet{
    private:
        card* list[150];
        card discard = card(-3);
    
    public:
        cardSet(){
            //create a set of cards. 
            //the set has 10 cards of each value from -2 to 12, except -2 which has 5 cards and 0 which has 15.
            for (int i=0;i<140;i+=14){ //10 cards of each, except -2
                list[i] = new card(-1);
                list[i+1] = new card(0);
                list[i+2] = new card(1);
                list[i+3] = new card(2);
                list[i+4] = new card(3);
                list[i+5] = new card(4);
                list[i+6] = new card(5);
                list[i+7] = new card(6);
                list[i+8] = new card(7);
                list[i+9] = new card(8);
                list[i+10] = new card(9);
                list[i+11] = new card(10);
                list[i+12] = new card(11);
                list[i+13] = new card(12);
            }
            for (int i = 0; i < 10; i+=2){ //5 cards of -2 and 5 additional cards of 0
                list[140+i] = new card(0);
                list[140+i+1] = new card(-2);
            }
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(&list[0], &list[150], g); //shuffle the set
        };

        card *topCard(){
            for (int i = 0; i < 150; i++){
                if (list[i]->getValue() != -3){
                    return list[i];
                }
            }
            exit(EXIT_FAILURE);
        }

        card *getCard(int index){
            return list[index];
        }

        void discardCard(card* card){
            discard.setValue(card->getValue());
        }

        card *getDiscard(){
            return &discard;
        }
};