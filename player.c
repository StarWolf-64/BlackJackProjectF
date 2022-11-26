#include <string.h>
#include "player.h"

const char *const COMPUTER_NAME = "Computer";
char *const PLAYER_NAME = "Player";
Player players[PLAYER_COUNT]; //initialize players

//makes all cards visible
void revealCards(Hand* hand ) {
    for (char i = 0; i < hand->cardsInHand; i++) {
        hand->cards[i]->hidden = false;
    }
}

//makes all cards in hand hidden
void hideCards(Hand* hand ) {
    for (char i = 0; i < hand->cardsInHand; i++) {
        hand->cards[i]->hidden = true;
    }
}

void playersInit() {
    players[0].score=10000000000000;//this is the dealer
    players[1].score=1000;
    players[2].score=1000;
    players[3].score=1000;
    players[4].score=1000;
    strcpy(players[0].name,COMPUTER_NAME);//this should be assumed to be the dealer
    strcpy(players[1].name,PLAYER_NAME);
    strcpy(players[2].name,PLAYER_NAME);
    strcpy(players[3].name,PLAYER_NAME);
    strcpy(players[4].name,PLAYER_NAME);
}
