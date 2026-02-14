Decks_game: main.o Card.o Deck.o
	g++ main.o Card.o Deck.o -o Decks_game

main.o: main.cpp Deck.h Card.h
	g++ -c main.cpp

Deck.o: Deck.cpp Deck.h Card.h
	g++ -c Deck.cpp
	
Card.o: Card.cpp Card.h
	g++ -c Card.cpp

clean:
	rm -f *.o Decks_game

