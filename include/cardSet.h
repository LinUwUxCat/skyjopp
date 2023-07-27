#include "card.h"
#include <random>
#include <algorithm>
#include <stack>

class cardSet{
    private:
        std::vector<card> list;
        std::vector<card> discard;
        
    public:
        cardSet(){
            //empty for now    
        };

        void createAndRandomize(){
            //create, then randomize the set of cards.
            //the set has 10 cards of each value from -2 to 12, except -2 which has 5 cards and 0 which has 15.
            for (int i=0;i<140;i+=14){ //10 cards of each, except -2
                list.push_back(card(-1));
                list.push_back(card(0));
                list.push_back(card(1));
                list.push_back(card(2));
                list.push_back(card(3));
                list.push_back(card(4));
                list.push_back(card(5));
                list.push_back(card(6));
                list.push_back(card(7));
                list.push_back(card(8));
                list.push_back(card(9));
                list.push_back(card(10));
                list.push_back(card(11));
                list.push_back(card(12));
            }
            for (int i = 0; i < 10; i+=2){ //5 cards of -2 and 5 additional cards of 0
                list.push_back(card(0));
                list.push_back(card(-2));
            }
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(list.begin(), list.end(), g); //shuffle the set
        }
//TODO: Implement a current_card in game or whatever, and don't set anything to -3. Put everything in a discard vector that will end up being reused when out of cards
        card &topCard(){
            if (list.size()>0) return list[list.size()-1];
            else exit(EXIT_FAILURE);
        }

        card getCard(int index){
            return list[index];
        }

        card takeTop(){
            if (list.size()<=0) exit(EXIT_FAILURE);
            card temp = list[list.size()-1];
            list.pop_back();
            return temp;
        }

        void discardCard(card* card){
            card->flip();
            discard.push_back(*card);
        }

        void discardCard(card card){
            card.flip();
            discard.push_back(card);
        }

        card *getDiscard(){
            if (discard.size()<=0) exit(EXIT_FAILURE);
            return &discard[discard.size()-1];
        }

        card swapDiscard(card c){
            if (discard.size()<=0) exit(EXIT_FAILURE);
            card temp = discard[discard.size()-1];
            discard[discard.size()-1] = c;
            return temp;
        }

        card swapDiscard(card* c){
            if (discard.size()<=0) exit(EXIT_FAILURE);
            card temp = discard[discard.size()-1];
            discard[discard.size()-1] = *c;
            return temp;
        }

};