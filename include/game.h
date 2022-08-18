#include "player.h"
#include <vector>

class game{
    private:
        std::vector<player*> players; //The official rules say 2 to 8 players.
        //it's better to use a vector here, because the number of players can change.
        cardSet set = cardSet();
        int numPlayers;
        //card discard = card(-3); //discard is now in the cardSet class

    public:
        game(std::vector<player*> players){
            //do not create the set here, since we do it each game start.
            this->numPlayers = players.size();
            this->players = players;
            //card setup
            
            

            //shuffle is already done hopefully. I should probably make a class for the set. there is a shuffle function in the main.cpp
            
            //deal
            //already done, will move tho

            //choose 2 initial cards to flip
            

        };

        void start(){
            int lastPlayer = -1;
            bool doublePoints = false;
            set.createAndRandomize(); //create and randomize set
                                      //now we can deal cards
            int cp = 0; //current player
            for (int i = 0; i < numPlayers*12; i++){
                players[cp]->setCard(i%12, set.getCard(i).getValue());
                if (i%12 == 11){
                    cp++;
                }
            }
            //discard
            this->set.getDiscard()->setValue(this->set.topCard().getValue()); //set the discard card to the top card.
            this->set.getDiscard()->flip();
            this->set.topCard().setValue(-3);
            for (int i = 0; i < numPlayers; i++){
                //std::cout << i << players[i]->getName() << std::endl;
                printf("%s, Choose 2 cards to flip:\n>> ", players[i]->getName());
                int card1, card2;
                int c;
                while (scanf("%d %d", &card1, &card2) != 2){
                    printf("Invalid input! Please try again\n>> ");
                    while((c = getchar()) != '\n' && c != EOF);
                }
                if (card1 > 11){
                    card1 = 11;
                }
                if (card2 > 11){
                    card2 = 11;
                }
                players[i]->getCard(card1)->flip();
                players[i]->getCard(card2)->flip();
            }
            std::cout << *this << std::endl;
            while (1){ //i hate doing this but oh well
                for (int i=0; i<numPlayers; i++){
                    if (lastPlayer == i){
                        printf("Finished!\n");
                        if (doublePoints){
                            players[lastPlayer]->addPoints(players[lastPlayer]->getPoints()*2);
                            printf("%s had more points than others, his points get doubled!\n", players[lastPlayer]->getName());
                        } //points handling must be done outside this class, or outside this for loop, which requires making another xd
                        return;
                    }
                    printf("It's %s's turn!", players[i]->getName());
                    printf("What do you want to do?\n0:Take a card from the stack\n1:Take the discarded card\n>> ");
                    int action = 0;
                    int c;
                    while (scanf("%d", &action) != 1){
                        printf("Invalid input! Please try again\n>> ");
                        while((c = getchar()) != '\n' && c != EOF);
                    }
                    if (action == 1){ //yes i know i'm not doing this in the right order
                        int cnum = -1;
                        while (cnum < 0 || cnum > 11){
                            printf("With what card do you want to swap the %s%d\033[0m you just took?\n>> ",set.getDiscard()->getColor(), set.getDiscard()->getValue());
                            scanf("%d", &cnum);
                            if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); }
                        }
                        action = players[i]->getCard(cnum)->getValue(); //hehe we already have an int variable, no need to create one more placeholder
                        players[i]->getCard(cnum)->setValue(set.getDiscard()->getValue());
                        players[i]->getCard(cnum)->flip();
                        set.getDiscard()->setValue(action);
                    } else {
                        printf("You picked a %s%d\033[0m!\nWhat will you do with it?\n0:Swap it with one of your cards\n1:Discard it\n>> ", this->set.topCard().getColor(), this->set.topCard().getValue());
                        int c;
                        while (scanf("%d", &action) != 1){
                            printf("Invalid input! Please try again\n>> ");
                            while((c = getchar()) != '\n' && c != EOF);
                        }
                        if (action == 0){ //this code sucks, it's repetitive
                            int cnum = -1;
                            while (cnum < 0 || cnum > 11){
                                printf("With what card do you want to swap the ");
                                printf(set.topCard().getColor());
                                printf("%d\033[0m you just took?\n>> ", set.topCard().getValue());
                                int c;
                                while (scanf("%d", &cnum) != 1){
                                    printf("Invalid input! Please try again\n>> ");
                                    while((c = getchar()) != '\n' && c != EOF);
                                }
                                if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); }
                            }

                            set.getDiscard()->setValue(players[i]->getCard(cnum)->getValue());
                            players[i]->getCard(cnum)->setValue(set.topCard().getValue());
                            players[i]->getCard(cnum)->flip();
                            set.topCard().setValue(-3);

                        } else {
                            int cnum = -1;
                            while (cnum < 0 || cnum > 11){
                                printf("You discarded the %d. Which card do you want to flip now?\n>> ", set.topCard().getValue());
                                int c;
                                while (scanf("%d", &cnum) != 1){
                                    printf("Invalid input! Please try again\n>> ");
                                    while((c = getchar()) != '\n' && c != EOF);
                                }
                                if (cnum < 0 || cnum > 11){ printf("Invalid Number! Please retry.\n>> "); } else if (players[i]->getCard(cnum)->getFacing()) { printf("You can't flip a card that's already flipped!\n"); cnum = -1;}
                            }
                            players[i]->getCard(cnum)->flip();
                            set.getDiscard()->setValue(set.topCard().getValue());
                            printf("Before : %d", set.topCard().getValue());
                            set.topCard().setValue(-3);
                            printf("After : %d", set.topCard().getValue());

                        }
                    }
                    players[i]->checkColumn();
                    printf("%s's turn ended! Here is the table : ", players[i]->getName());
                    std::cout << *this << std::endl ;
                    if (players[i]->checkWin() && lastPlayer == -1){
                        lastPlayer = i;
                        printf("%s has started the last round!\n", players[i]->getName());
                    }
                    if (lastPlayer != -1 && i != lastPlayer){
                        if (players[lastPlayer]->getTotal() > players[i]->getTotal() && !doublePoints){
                            doublePoints = true;
                        }
                        players[i]->addPoints(players[i]->getTotal());
                    }
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& out, game myGame){
            out << "Discard: " << myGame.set.getDiscard()->getColor() << myGame.set.getDiscard()->getValue() << "\033[0m" << "\n";
            for (int i = 0; i < myGame.numPlayers; i++){
                out << *myGame.players[i] << std::endl;
            }
            return out;
        }

};