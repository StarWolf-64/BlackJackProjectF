# makes card_demo
# % make
# % make card_demo
# % make clean
all: playblackjack

FLAGS = -Wall -Wno-char-subscripts
card_demo: blackjack.c card.h card.c deck.c deck.h player.c player.h
	@echo 'building playblackjack.'
	gcc -o playblackjack blackjack.c card.c deck.c player.c $(FLAGS)

clean:
	rm -f playblackjack *.o

