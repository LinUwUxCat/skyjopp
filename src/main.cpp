#include <iostream>
#include "game.h" //includes the game, which also includes player which also includes card and spacefill.

int main(){ //half of this will disappear lol
    cardSet mySet = cardSet();
    int numPlayers; //actually let's create players here
    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);
    if (numPlayers > 8){ //The official rules say 2 to 8 players.
        printf("Too many players.\n");
        return 1;
    } else if(numPlayers < 2){
        printf("Too few players.\n");
       return 1;
    }
    player *players[numPlayers]; 
    for (int i = 0; i < numPlayers; i++){
        printf("Enter the name of player %d: ", i+1);
        char name[20]; //maybe this is too short?
        scanf("%s", name);
        players[i] = new player(name, mySet);
    //    std::cout << i << players[i]->getName() << std::endl;
    }
    
    
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
    game g = game(numPlayers, players, mySet);
    g.start();
    for (int i = 0; i < numPlayers; i++){
        std::cout << players[i]->getName() << "has" << players[i]->getPoints() << "points." << std::endl;
    }

    return 0;

}
