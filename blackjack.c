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
	int gamego = 1;
	int playersuse = 5;
	int loopcount = 0;

	//main game loop
	while(gamego){
		
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
		printf("loop iteration %d\n", loopcount);
		loopcount++;

	}

}
