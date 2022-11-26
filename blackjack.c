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
	printf("Game start\n");

	//game loop ending conditions
	int gamego = 1; //while loop condition statement
	int playersuse = 2; //minimum 2 players, first player is always dealer
	int loopcount = 0; //test code

	//main game loop
	while(gamego){
		
		//shuffle deck each game
		shuffleDeck(shuffled, deck);

		//game/turn loop
		int contgame = 4;
		int loopnum = 0;
		while(contgame){
			
			//refresh continue condition
			contgame = 4;

			//deal cards:
			//deal to dealer (First loop only until all players are fold/bust)
			if(loopnum == 0){
				deal(shuffled, &players[i].hand, 2);
			}

			//deal to players
			for(int i = 1; i < playersuse; i++){
				if(loopnum > 0){
					deal(shuffled, &players[i].hand, 2);
				}
				else{
					deal(shuffled, &players[i].hand, 1);
				}

				//test print
				printf("Player %d's hand:\n",i);
				printCards(players[i].hand.cards, 0, 2);
			}

			//player fold/bust condition
			for(int i = 1; i < playersuse; i++){
				int cardsum = 0;
				for(int j = 0; j < 2; j++){
					cardsum += players[i].hand.cards[j].value;
				}
				
				if(cardsum > 21){
					contgame--;
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
			//printf("player %d score = %d\n", i, players[i].score);
			players[i].score = players[i].score - 50;
			//printf("player %d new score = %d\n", i, players[i].score);
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
		//printf("loop iteration %d\n", loopcount);
		loopcount++;

	}

	printf("GAME OVER\n");
	printf("Final scores:\n");
	for(int i = 1; i < playersuse; i++){
        	printf("player %d score = %d\n", i, players[i].score);
        }

}
