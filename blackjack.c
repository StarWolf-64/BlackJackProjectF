//Bryan Potts, Nahom Tilahun
#include <stdio.h>
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode
#include "deck.h"
#include "card.h"
#include "player.h"

#define PLAYER_COUNT 5
extern Player players[PLAYER_COUNT]; //initialize players
const static char *RESET_COLOR = "\x1b[36m";

Card deck[DECK_SIZE];
Card *shuffled[DECK_SIZE];

int main(int argc, char **argv){
	printf("%s",RESET_COLOR); //default color
	initCard(); // set up unicode printing
	initDeck(deck);// makes the memory for the deck
	shuffleDeck(shuffled, deck); //shuffledeck shuffles the deck
	playersInit();
	system("clear"); //clear console
	printf("Game start\n");

	//game loop ending conditions
	int gamego = 1; //while loop condition statement
	int playersuse = 2; //minimum 2 players, first player is always dealer
	int loopcount = 0; //test code

	//main game loop
	while(gamego){
		
		//shuffle deck each game and reset player values
		shuffleDeck(shuffled, deck);
		for(int i = 0; i < playersuse; i++){
			players[i].hand.cardsInHand = 0;
		}

		//tracking values for loop
		int playergo[5] = {1, 1, 1, 1, 1};
		int scoremod[5] = {0, 0, 0, 0, 0};

		//game/turn loop
		int contgame = playersuse - 1;
		int loopnum = 0;
		while(contgame){
			
			//refresh continue condition
			contgame = playersuse - 1;

			//deal cards:
			//deal to dealer (First loop only until all players are fold/bust)
			if(loopnum == 0){
				deal(shuffled, &players[0].hand, 2);
			}

			//deal to players
			for(int i = 1; i < playersuse; i++){
				if(loopnum == 0){
					deal(shuffled, &players[i].hand, 2);
				}
				else{
					Hand *hand0 = &players[i].hand;
					hand0->cards[players[i].hand.cardsInHand] = draw(shuffled);
					//printf("Cards: %d\n", players[i].hand.cardsInHand);
					players[i].hand.cardsInHand++;
					//printf("Cards NEW: %d\n", players[i].hand.cardsInHand);
				}

				//test print
				printf("Player %d's hand:\n",i);
				printCards(players[i].hand.cards, 0, players[i].hand.cardsInHand);
			}

			//player fold/bust condition
			for(int i = 1; i < playersuse; i++){
				int cardsum = 0;
				for(int j = 0; j < players[i].hand.cardsInHand; j++){
					cardsum += players[i].hand.cards[j]->value;
				}
				
				printf("sum: %d\n", cardsum);

				if(cardsum == 21){
					contgame--;
					playergo[i] = 0;
					scoremod[i] = 1;
				}
				else if(cardsum > 21){
					contgame--;
					playergo[i] = 0;
					scoremod[i] = 0;
				}
			}

			//increment loop number
			loopnum++;

			//emergency catch condition
			if(loopnum > 5){
				contgame = 0;
			}
		}

		//test code
		for(int i = 1; i < playersuse; i++){
			printf("player %d score = %d\n", i, players[i].score);
			if(scoremod[i] == 1){
				players[i].score = players[i].score + 50;
			}
			else if(scoremod[i] == 0){
				players[i].score = players[i].score - 50;
			}
			printf("player %d new score = %d\n", i, players[i].score);
		}

		//get sum of all player scores
		int scoresum = 0;//
		for(int i = 1; i < playersuse; i++){
			scoresum += players[i].score;
		}

		//end while loop check
		int endcheck = 10 * playersuse;
		if(scoresum <  endcheck){
			gamego = 0;
		}
		
		//test code
		printf("loop iteration %d\n", loopcount);
		loopcount++;

	}

	printf("GAME OVER\n");
	printf("Final scores:\n");
	for(int i = 1; i < playersuse; i++){
        	printf("player %d score = %d\n", i, players[i].score);
        }

}
