#include "player.h"
class game{
    protected:
        player *players[8]; //The official rules say 2 to 8 players.
        card* set[150];
        int numPlayers;
        card discard = card(-3);

    public:
        game(card* set[150], int numPlayers,  player* players[8]){
            for (int i = 0; i < 150; i++){
                this->set[i] = set[i];
            }
            this->numPlayers = numPlayers;
            for (int i = 0; i < this->numPlayers; i++){
                this->players[i] = players[i];
            }
            
            //std::cout << numPlayers << std::endl;
            //card setup
            discard.setValue(topCard()->getValue()); //set the discard card to the top card.
            discard.flip();
            topCard()->setValue(-3);

            //shuffle is already done hopefully. I should probably make a class for the set. there is a shuffle function in the main.cpp
            
            //deal
            //already done, will move tho

            //choose 2 initial cards to flip
            for (int i = 0; i < numPlayers; i++){
                //std::cout << i << players[i]->getName() << std::endl;
                printf("%s, Choose 2 cards to flip:\n>> ", players[i]->getName());
                int card1, card2;
                scanf("%d %d", &card1, &card2);
                players[i]->getCard(card1)->flip();
                players[i]->getCard(card2)->flip();
            }
            std::cout << *this << std::endl;

        };

        card* topCard(){
            for (int i = 0; i < 150; i++){
                if (set[i]->getValue() != -3){
                    return set[i];
                }
            }
            exit(EXIT_FAILURE);
        };
        
        void start(){
            int lastPlayer = -1;
            while (1){ //i hate doing this but oh well
                for (int i=0; i<numPlayers; i++){
                    if (lastPlayer == i){
                        printf("Finished!\n");
                        return;
                    }
                    printf("It's %s's turn!", players[i]->getName());
                    printf("What do you want to do?\n0:Take a card from the stack\n1:Take the discarded card\n>> ");
                    int action = 0;
                    scanf("%d", &action);
                    if (action == 1){ //yes i know i'm not doing this in the right order
                        int cnum = -1;
                        while (cnum < 0 || cnum > 11){
                            printf("With what card do you want to swap the %d you just took?\n>> ", discard.getValue());
                            scanf("%d", &cnum);
                            if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); }
                        }
                        action = players[i]->getCard(cnum)->getValue(); //hehe we already have an int variable, no need to create one more placeholder
                        players[i]->getCard(cnum)->setValue(discard.getValue());
                        players[i]->getCard(cnum)->flip();
                        discard.setValue(action);
                    } else {
                        printf("You picked a %d!\nWhat will you do with it?\n0:Swap it with one of your cards\n1:Discard it\n>> ", topCard()->getValue());
                        scanf("%d", &action);
                        if (action == 0){ //this code sucks, it's repetitive
                            int cnum = -1;
                            while (cnum < 0 || cnum > 11){
                                printf("With what card do you want to swap the ");
                                printf(topCard()->getColor());
                                printf("%d\033[0m you just took?\n>> ", topCard()->getValue());
                                scanf("%d", &cnum);
                                if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); }
                            }

                            discard.setValue(players[i]->getCard(cnum)->getValue());
                            players[i]->getCard(cnum)->setValue(topCard()->getValue());
                            players[i]->getCard(cnum)->flip();
                            topCard()->setValue(-3);

                        } else {
                            int cnum = -1;
                            while (cnum < 0 || cnum > 11){
                                printf("You discarded the %d. Which card do you want to flip now?\n>> ", topCard()->getValue());
                                scanf("%d", &cnum);
                                if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); } else if (players[i]->getCard(cnum)->getFacing()) { printf("You can't flip a card that's already flipped!\n"); cnum = -1;}
                            }
                            players[i]->getCard(cnum)->flip();
                            discard.setValue(topCard()->getValue());
                            topCard()->setValue(-3);
                        }
                    }
                    players[i]->checkColumn();
                    printf("%s's turn ended! Here is the table : ", players[i]->getName());
                    std::cout << *this << std::endl ;
                    if (players[i]->checkWin()){
                        lastPlayer = i;
                        printf("%s has started the last round!\n", players[i]->getName());
                    }
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& out, game myGame){
            out << "Discard: " << myGame.discard.getColor() << myGame.discard.getValue() << "\033[0m" << "\n";
            for (int i = 0; i < myGame.numPlayers; i++){
                out << *myGame.players[i] << std::endl;
            }
            return out;
        }

};