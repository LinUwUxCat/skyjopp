#include <iostream>
#include <string>
#include "cardSet.h"
#include "utils.h"

class player{
    private:
        char name[20];
        card table[12] = {card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3)}; //so since the size will never change, there's no need for a vector.
        int points = 0;
    
    public:
        player(char* name){ //do i really need to pass the set? //this will be moved later
            strcpy(this->name, name);
            /*int offset = 0;
            for (int i = 0; i < 12; i++){
                if (set.getCard(i+offset)->getValue() != -3){
                    table[i].setValue(set.getCard(i+offset)->getValue());
                    set.getCard(i+offset)->setValue(-3);
                } else {
                    i--;
                    offset++;
                }
            }*/
        };
        void setName(char* name){
            strcpy(this->name, name);
        };
        char* getName(){
            return name;
        }
        card* getCard(int index){
            return &table[index];
        };
        void setCard(int index, card card){
            table[index] = card;
        };

        card* getTable(){
            return table;
        };    

        void resetTable(){
            for (int i = 0; i < 12; i++){
                table[i].setValue(-3);
            }
        }

        int getTotal(){
            int total = 0;
            for (int i = 0; i < 12; i++){
                if (table[i].getFacing()){
                    total += table[i].getValue();
                }
            }
            return total;
        };

        bool checkWin(){
            for (int i = 0; i< 12; i++){
                if (!table[i].getFacing()){
                    return false;
                }
            }
            return true;
        };

        int getPoints(){
            return points;
        };

        void addPoints(int points){
            this->points += points;
        };


        
        void checkColumn(){
            for (int i = 0; i < 4; i++){
                if (table[i].getValue() == table[i+4].getValue() && table[i+4].getValue() == table[i+8].getValue() && table[i].getFacing() && table[i+4].getFacing() && table[i+8].getFacing()){
                    table[i].disable();
                    table[i+4].disable();
                    table[i+8].disable();
                }
            }
            return;
        }

        //this function is used to print the player's hand.
        //it will only work with the << operator, for example using std::cout << p1 << std::endl;
        //as such, printf("%s", p1) will not work.
        //This function will print the player's name, followed by a newline, and then the cards in the player's hand.
        friend std::ostream& operator<<(std::ostream& out, player myPlayer){
            out << myPlayer.getName() << ":\n";
            for (int i = 0; i < 12; i++){
                if (!myPlayer.getCard(i)->getFacing()){ 
                    out << "?   "; 
                } else if (!myPlayer.getCard(i)->getEnabled()){
                    out << "\033[38;5;244m" << spacefill((char*)std::to_string(myPlayer.getCard(i)->getValue()).c_str(), 3) << " \033[0m";
                } else {
                    out << myPlayer.getCard(i)->getColor() << spacefill((char*)std::to_string(myPlayer.getCard(i)->getValue()).c_str(), 3) << " \033[0m"; //only 2 is necessary but 3 looks better
                }
                if (i == 3){
                    out << "\tTotal : " << myPlayer.getTotal() << "\n";
                }
                if (i == 7){
                    out << "\tPoints : " << myPlayer.getPoints() << "\n";
                }
            }
            out << std::endl;
            return out;
        };
        
};

bool noPlayersAboveMax(std::vector<player*> players, int maxPoints){
    for (int i = 0; i < players.size(); i++){
        if (players[i]->getPoints() > maxPoints){
            return false;
        }
    }
    return true;
}