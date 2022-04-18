#include "player.h"
class game{
    protected:
        player *players[8]; //The official rules say 2 to 8 players.
        int numPlayers;
        card* set[150];
        card discard = card(-3);

    public:
        game(card* set[150]){
            for (int i = 0; i < 150; i++){
                this->set[i] = set[i];
            }
            printf("Enter the number of players: ");
            scanf("%d", &numPlayers);
            if (numPlayers > 8){
                printf("Too many players.\n");
                exit(1);
            } else if(numPlayers < 2){
                printf("Too few players.\n");
                exit(1);
            }
            //player creation
            for (int i = 0; i < numPlayers; i++){
                printf("Enter the name of player %d: ", i+1);
                char name[20]; //maybe this is too short?
                scanf("%s", name);
                players[i] = new player(name, set);
            }
            //card setup
            discard.setValue(topCard()->getValue()); //set the discard card to the top card.
            discard.flip();
            topCard()->setValue(-3);

            //shuffle is already done hopefully. I should probably make a class for the set. there is a shuffle function in the main.cpp
            
            //deal
            //already done, will move tho

            //choose 2 initial cards to flip
            for (int i = 0; i < numPlayers; i++){
                printf("Choose 2 cards to flip:\n>> ");
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
            bool notDone = true;
            while (notDone){
                for (int i=0; i<numPlayers; i++){
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
                                printf("With what card do you want to swap the %d you just took?\n>> ", topCard()->getValue());
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
                                if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); }
                            }
                            players[i]->getCard(cnum)->flip();
                        }
                    }
                    printf("%s's turn ended! Here is the table : ", players[i]->getName());
                    std::cout << *this << std::endl ;
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