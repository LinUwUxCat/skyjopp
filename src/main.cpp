#include <iostream>
#include <algorithm>
#include <random>
#include "game.h" //includes the game, which also includes player which also includes card and spacefill.

void createSet(card* set[150]){ 
    //create a set of cards. 
    //the set has 10 cards of each value from -2 to 12, except -2 which has 5 cards and 0 which has 15.
    for (int i=0;i<140;i+=14){ //10 cards of each, except -2
        set[i] = new card(-1);
        set[i+1] = new card(0);
        set[i+2] = new card(1);
        set[i+3] = new card(2);
        set[i+4] = new card(3);
        set[i+5] = new card(4);
        set[i+6] = new card(5);
        set[i+7] = new card(6);
        set[i+8] = new card(7);
        set[i+9] = new card(8);
        set[i+10] = new card(9);
        set[i+11] = new card(10);
        set[i+12] = new card(11);
        set[i+13] = new card(12);
    }
    for (int i = 0; i < 10; i+=2){ //5 cards of -2 and 5 additional cards of 0
        set[140+i] = new card(0);
        set[140+i+1] = new card(-2);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(&set[0], &set[150], g); //shuffle the set
}

int main(){ //half of this will disappear lol
    card* set[150];
    createSet(set);
    /*for (int i = 0; i < 150; i++){
        std::cout << set[i]->getValue() << " ";
    }
    std::cout << "end" << std::endl;
    player p1 = player("Joe", set);
    player p2 = player("Bob", set);
    std::cout << p1 << p2 << std::endl;
    printf("Choose 2 cards to flip:\n");
    int card1, card2;
    scanf("%d %d", &card1, &card2);
    p1.getCard(card1)->flip();
    p1.getCard(card2)->flip();
    std::cout << p1 << std::endl;*/
    game g = game(set);
    g.start();

    return 0;

}
