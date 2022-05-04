#include <string.h>


char* spacefill(char* str, int n){
    int len = strlen(str);
    if (len >= n){
        return str;
    }
    int diff = n - len;
    for (int i = 0; i < diff; i++){
        strcat(str, " ");
    }
    return str;
}

bool noPlayersAboveMax(player* players[8], int numPlayers, int maxPoints){
    for (int i = 0; i < numPlayers; i++){
        if (players[i]->getPoints() > maxPoints){
            return false;
        }
    }
    return true;
}