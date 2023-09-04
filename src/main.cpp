#include <iostream>
#include <vector>
#include "game.h" //includes the game, which also includes player which also includes card and spacefill.
#include "render.hpp"

int main(){ //half of this will disappear lol

    Renderer R = Renderer();

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
    std::vector<player*> players;
    for (int i = 0; i < numPlayers; i++){
        printf("Enter the name of player %d: ", i+1);
        char name[20]; //maybe this is too short?
        scanf("%s", name);
        players.push_back(new player(name));
    //    std::cout << i << players[i]->getName() << std::endl;
    }
    
    game g = game(players);
    while ( noPlayersAboveMax(players, 100) ){ //the official rules say that the game ends when 1 player has 100 points.
        g.start();
        for (int i = 0; i < numPlayers; i++){
            std::cout << players[i]->getName() << " now has " << players[i]->getPoints() << " points." << std::endl;
        }
    }
    return 0;

}
