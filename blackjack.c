//Bryan Potts, Nahom Tilahun
#include <stdlib.h>
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
	printf("Welcome to\n\n");
	printf("	 ____  _            _       _            _        \n");
	printf("	| __ )| | __ _  ___| | __  | | __ _  ___| | __    \n");
	printf("	|  _ \\| |/ _` |/ __| |/ /  | |/ _` |/ __| |/ /    \n");
	printf("	| |_) | | (_| | (__|   < |_| | (_| | (__|   <     \n");
	printf("	|____/|_|\\__,_|\\___|_|\\_\\___/ \\__,_|\\___|_|\\_\\    \n");
	printf("\n\n");

	//display game rules
	printf("Standard Blackjack rules with no double down, no split, dealer wins on tie\n");
	printf("All bets between 10-500, bets over remaining score is the same as All-in\n\n");
	
	//game loop ending conditions
	int gamego = 1; //while loop condition statement
	int playersuse = 2; //minimum 2 players, first player is always dealer
	int loopcount = 0; //test code
	//this determines the amount of players who will play the game
	int playerNum;
	printf("How many human players do you want? Please enter a number from 1-4\n");//prompt for user input
	scanf("%d",&playerNum);//store user input
	switch(playerNum){
		case 1:
			printf("You have 1 human player\n");//you have 1 human players (keep in mind dealer always plays)
			playerNum++;
			playersuse=playerNum;
			break;
		case 2:
		        printf("You have 2 human players\n");//you have 2 human players
			playerNum++;
			playersuse=playerNum;
			break;
		case 3:
		        printf("You have 3 human players\n");//you have 3 human players
			playerNum++;
			playersuse=playerNum;
			break;
		case 4:
			printf("You have 4 human players\n");//you have 4 human players
			playerNum++;
			playersuse=playerNum;
			break;
		default:
			printf("You entered invalid input try again ya silly goose :<\n");
			exit(-1);

	}



	//other variables
	int remaining = 52; //number of remaining cards in shuffled
	int bet[5] = {100, 100, 100, 100, 100}; //bets and starting value
	int betvalue;

	//put something here to prompt players for their starting bets
	for(int i=1;i<playersuse;i++){
		printf("Player %d, What do you want your starting bet to be. Use a number between 10-500\n", i);//starting bet question
		scanf("%d",&betvalue);//stores the value of the starting bet
		if(betvalue<=500 && betvalue>=10){//if number is between 10 and 500
			//change the value of their bet dependent on value entered
			bet[i]=betvalue;
		}
		else{
			printf("You did not enter a bet value that was in the range. Your starting bet value remains at a value of 100\n");
		}
	}

	//main game loop
	while(gamego){
		system("clear");
		
		//shuffle deck each game and reset player values
		//initCard();
		//initDeck(deck);
		shuffleDeck(shuffled, deck);
		for(int i = 0; i < playersuse; i++){
			players[i].hand.cardsInHand = 0;
		}

		//tracking values for loop
		int playergo[5] = {1, 1, 1, 1, 1};// 1 means hit & 0 means fold
		int scoremod[5] = {0, 0, 0, 0, 0};
		char valueOfQ='h';//char representation for question assume h intially
		int  iValueOfQ=1; //comparaing result of valueOfQ to adjust to playergo which determines if it holds or hits assume 1 intially

		//game/turn loop
		int contgame = playersuse - 1;
		int loopnum = 0;//what number of loop we are on for first loop we don't want to ask for hit or fold
		while(contgame){
			//loop variables
			int playersums[5] = {0, 0, 0, 0, 0}; //sum of players scores for quick access

			//refresh continue condition
			contgame = playersuse - 1;
			if(loopnum>0){
				for(int i=1;i<playersuse;i++){
					if(playergo[i] != 0){
						printf("%s %d %s\n","Player ", i, " enter h or f for hit or fold\n");
					        scanf("%s",&valueOfQ);
						if(valueOfQ=='h'){
							iValueOfQ=1;//update value
							playergo[i]=iValueOfQ;//updates the value of playergo array
	
						}
						else{
							 iValueOfQ=0;//update value
							 playergo[i]=iValueOfQ;//updates the value of playergo array
						}
					}
				}

			}

			//deal cards:
			//deal to dealer (First loop only until all players are fold/bust)
			if(loopnum == 0){
				deal(shuffled, &players[0].hand, 2);
				remaining -= 2;

				//print the dealers cards, NOTE: this is long because printing one red card and one green card is hard
				printf("The Dealer's cards:\n");
				Card *c = players[0].hand.cards[0];
				Card *c2 = players[0].hand.cards[1];
				c->hidden = 1;
				c->selected = 1;
				printPartOfCard(c, 0);
				c2->hidden = 0;
				c2->selected = 0;
				printPartOfCard(c2, 0);
				printf("\n");
				c->hidden = 1;
				c->selected = 1;
				printPartOfCard(c, 1);
				c2->hidden = 0;
				c2->selected = 0;
				printPartOfCard(c2, 1);
				printf("\n");
				c->hidden = 1;
				c->selected = 1;
				printPartOfCard(c, 2);
				c2->hidden = 0;
				c2->selected = 0;
				printPartOfCard(c2, 2);
				printf("\n");
				//printCards(players[0].hand.cards, 1, 2);
				//Card *c2 = players[0].hand.cards[1];
				//c2->hidden = 0;
				//c2->selected = 0;
				//printCard(c2, "\n");

			}

			//deal to players
			for(int i = 1; i < playersuse; i++){
				if(loopnum == 0){
					deal(shuffled, &players[i].hand, 2);
					remaining -= 2;
				}
				else if(loopnum > 0 && playergo[i] == 1){
					Hand *hand0 = &players[i].hand;
					hand0->cards[players[i].hand.cardsInHand] = draw(shuffled);
					//printf("Cards: %d\n", players[i].hand.cardsInHand);
					players[i].hand.cardsInHand++;
					//printf("Cards NEW: %d\n", players[i].hand.cardsInHand);
					remaining--;
				}

				//test print
				printf("Player %d's hand:\n",i);
				printCards(players[i].hand.cards, 0, players[i].hand.cardsInHand);
			}

			//player fold/bust condition
			for(int i = 1; i < playersuse; i++){
				int hasace = 0;
				int cardsum = 0;
				for(int j = 0; j < players[i].hand.cardsInHand; j++){
					int tempval = players[i].hand.cards[j]->value;
					if(tempval == 1){
						int tempsum = cardsum;
						tempsum += 11;
						if(tempsum > 21){
							cardsum += 1; //ace partial value
						}
						else{
							cardsum += 11; //ace full value
							hasace++;
						}
					}
					else if(tempval > 10){
						cardsum += 10;
					}
					else{
						cardsum += players[i].hand.cards[j]->value;
					}
				}
				
				printf("The sum of Player %d's hand is: %d\n", i ,cardsum);
				playersums[i] = cardsum;

				if(cardsum == 21){
					contgame--;
					playergo[i] = 0;
					//scoremod[i] = 1;
				}
				else if(cardsum > 21){
					while((cardsum > 21) && (hasace > 0)){
						//switches full value aces to small value if bust
						cardsum -= 10;
						hasace--;
					}
			
					//if still over 21 then bust
					if(cardsum > 21){
						contgame--;
						playergo[i] = 0;
						//scoremod[i] = 0;
					}
				}
				else if(cardsum < 21 && playergo[i] == 0){
					contgame--;
				}
			}

			//calculate dealer cards and draw if less than 16
			int dealersum = 0;
			if(contgame == 0){
				//print dealers cards with revealed card
				printf("The Dealer's cards:\n");
				Card *c = players[0].hand.cards[0];
				Card *c2 = players[0].hand.cards[1];
				c->hidden = 0;
				c->selected = 1;
				printPartOfCard(c, 0);        
				c2->hidden = 0;    
				c2->selected = 0;    
				printPartOfCard(c2, 0);   
				printf("\n");       
				c->hidden = 0;       
				c->selected = 1;    
				printPartOfCard(c, 1);    
				c2->hidden = 0;      
				c2->selected = 0;      
				printPartOfCard(c2, 1);     
				printf("\n");       
				c->hidden = 0;    
				c->selected = 1;    
				printPartOfCard(c, 2);        
				c2->hidden = 0;       
				c2->selected = 0;    
				printPartOfCard(c2, 2);   
				printf("\n");

				//sum the dealers cards
				for(int i = 0; i < players[0].hand.cardsInHand; i++){
					dealersum += players[0].hand.cards[i]->value;	
				}

				//draw until sum is greater than or equal to 16
				int dealerace = 0;
				while(dealersum < 16){
					//printf("dealersum: %d\n", dealersum);
					Hand *hand0 = &players[0].hand;   
					hand0->cards[players[0].hand.cardsInHand] = draw(shuffled);

					//display new card
					printf("Dealer draws a card:\n");
					players[0].hand.cards[players[0].hand.cardsInHand]->hidden = 0;
					printCard(players[0].hand.cards[players[0].hand.cardsInHand], "\n");

					//calculate new card sum
					int cardval = players[0].hand.cards[players[0].hand.cardsInHand]->value;
					if(cardval == 1){
						int tempcalc = dealersum;
						tempcalc += 11;
						if(tempcalc > 21){
							dealersum += 1;	//ace smaller value to prevent bust
						}
						else{
							dealersum += 11; //ace full value
							dealerace++;
						}
					}
					else if(cardval > 10){
						dealersum += 10;
					}
					else{
						dealersum += players[0].hand.cards[players[0].hand.cardsInHand]->value;
					}
					players[0].hand.cardsInHand++;

					//if dealer bust and has ace, reduce ace value
					while((dealersum > 21) && (dealerace > 0)){
						dealersum -= 10;
						dealerace--;
					}
					
				}

				printf("The sum of the dealer's cards is: %d\n", dealersum);

			}

			//decide winner(s)
			if(dealersum > 21){
				//everyone wins	
				for(int i = 1; i < playersuse; i++){
					scoremod[i] = 1;
				}
				printf("Dealer Bust! All players win!\n");
			}
			else if(dealersum == 21){
				//everyone loses
				for(int i = 1; i < playersuse; i++){   
					scoremod[i] = 0;
				}
				printf("Dealer has 21. All players lose.\n");
			}
			else if((dealersum < 21) & (contgame <= 0)){
				//case by case basis
				for(int i = 1; i < playersuse; i++){ 
					if(playersums[i] == 21){
						scoremod[i] = 2;
						printf("Player %d has 21 and wins!\n", i);	
					}
					else if(playersums[i] < 21){
						if(playersums[i] > dealersum){
							scoremod[i] = 1;
							printf("Player %d has a greater hand than the Dealer. Player %d wins!\n",i,i);
						}
						else if(playersums[i] == dealersum){ 
							scoremod[i] = 0;   
							printf("Player %d has an equal hand to the Dealer. Dealer wins.\n",i);
						}
						else{
							scoremod[i] = 0;
							printf("Player %d has a lesser hand than the Dealer. Dealer wins.\n",i);
						}
					}
					else{
						scoremod[i] = 0;
						printf("Player %d has busted! Dealer wins.\n",i);
					}
				}
			}

			
			//increment loop number
			loopnum++;

			//emergency catch condition
			if(loopnum > 10){
				contgame = 0;
			}

			//printRestOfDeck(shuffled);
		}
	
		/*
		//return hands to shuffled deck (don't worry it will get re shuffled again before dealing)
		for(int i = 0; i < playersuse; i++){
			for(int j = 0; j < players[i].hand.cardsInHand; j++){
				shuffled[remaining] = players[i].hand.cards[j];
				remaining++;
			}
		}
		*/

		resetIndex();
		remaining = 52;

		//score modulation
		for(int i = 1; i < playersuse; i++){
			//printf("player %d score = %d\n", i, players[i].score);
			if(scoremod[i] == 1){
				players[i].score = players[i].score + bet[i];
			}
			else if(scoremod[i] == 0){
				players[i].score = players[i].score - bet[i];
			}
			else if(scoremod[i] == 2){
				//natural 21
				players[i].score = players[i].score + (bet[i] * 2.5);
			}

			//convert negative scores to 0
			if(players[i].score < 0){
				players[i].score = 0;
			}

			printf("player %d's score = %d\n", i, players[i].score);
		}

		//get sum of all player scores
		int scoresum = 0;//
		for(int i = 1; i < playersuse; i++){
			scoresum += players[i].score;
		}

		//end while loop check
		int endcheck = 10 * (playersuse - 1);
		if(scoresum <  endcheck){
			gamego = 0;
		}
		
		//test code
		//player input for quitting, raising bet
		int betOrQ;
		int changedBet;
		for(int i=1;i<playersuse;i++){
			printf("Player %d, Do you want to quit the game,keep your bet the same or change your bet? Enter 1 for changing bet, 2 to quit & 3 to not change the bet.\n", i);
			scanf("%d",&betOrQ);//store user input if you
			if(gamego > 0){
		
				switch(betOrQ){
					case 1://change bet condition 
				       		printf("Player %d, What do you want to change your bet to. Use a number between 10-500\n", i);//changed bet
						scanf("%d",&changedBet);//stores the value of changed bet
						if(changedBet<=500 && changedBet>=10){
							bet[i]=changedBet;
						}
						else{
							printf("You did not input a bet value in the range. Your bet value was not changed.");
						}
						
						break;
					case 2://Quit condition
						gamego = 0;//you want to change value of gamego to quit the game
						break;
					case 3://you want the bet the same
						break;
					default://you gave bad input
					       	printf("You entered invalid input dude. For the next time please put in valid input :)\n");
						break;
				}
			}
		}
		//printf("loop iteration %d\n", loopcount);
		loopcount++;

	}

	 //code to store the value of highscores into the a text file
	char *filename = "highscore.txt";//the text file to be created
       	FILE *fp=fopen(filename,"a");//it will read and write to the file and if it doesn't exist and append to file	                                
	printf("GAME OVER\n");
	printf("Final scores:\n");
	for(int i = 1; i < playersuse; i++){
        	printf("player %d score = %d\n", i, players[i].score);
		scanf("%d",&players[i].score);
		fprintf(fp,"%d",players[i].score);
        }
	fclose(fp);
}
