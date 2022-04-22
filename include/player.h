#include <iostream>
#include <string>
#include "card.h"
#include "spacefill.h"

class player{
    protected:
        char name[20];
        card table[12] = {card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3),card(-3)};
        
    
    public:
        player(char* name, card* set[150]){ //do i really need to pass the set?
            strcpy(this->name, name);
            int offset = 0;
            for (int i = 0; i < 12; i++){
                if (set[i+offset]->getValue() != -3){
                    table[i].setValue(set[i+offset]->getValue());
                    set[i+offset]->setValue(-3);
                } else {
                    i--;
                    offset++;
                }
            }
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

        int getTotal(){
            int total = 0;
            for (int i = 0; i < 12; i++){
                total += table[i].getValue();
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
                if (i == 3 || i == 7){
                    out << "\n";
                }
            }
            out << std::endl;
            return out;
        };
        
};