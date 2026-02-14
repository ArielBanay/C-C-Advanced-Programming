Decks_game: main.o Troll.o Sorcerer.o Ranger.o Player.o Ghost.o Fighter.o Enemy.o Dragon.o Deck.o Card.o Entity.o
	g++ main.o Troll.o Sorcerer.o Ranger.o Player.o Ghost.o Fighter.o Enemy.o Dragon.o Deck.o Card.o Entity.o -o Decks_game

main.o: main.cpp Deck.h Card.h Defs.h Dragon.h Enemy.h Fighter.h Player.h Ghost.h Ranger.h Sorcerer.h Troll.h
	g++ -c main.cpp

Fighter.o: Fighter.cpp Fighter.h Player.h Defs.h Card.h Enemy.h Entity.h
	g++ -c Fighter.cpp
	
Ranger.o: Ranger.cpp Ranger.h Player.h Defs.h Card.h Enemy.h Entity.h
	g++ -c Ranger.cpp

Sorcerer.o: Sorcerer.cpp Sorcerer.h Player.h Defs.h Card.h Enemy.h Entity.h
	g++ -c Sorcerer.cpp

Dragon.o: Dragon.cpp Dragon.h Enemy.h Defs.h Card.h Entity.h
	g++ -c Dragon.cpp

Ghost.o: Ghost.cpp Ghost.h Enemy.h Defs.h Card.h Entity.h
	g++ -c Ghost.cpp

Troll.o: Troll.cpp Troll.h Enemy.h Defs.h Card.h Entity.h
	g++ -c Troll.cpp

Player.o: Player.cpp Player.h Defs.h Card.h Enemy.h Entity.h
	g++ -c Player.cpp

Enemy.o: Enemy.cpp Enemy.h Defs.h Card.h Entity.h
	g++ -c Enemy.cpp
	
Entity.o: Entity.h Entity.cpp
	g++ -c Entity.cpp

Deck.o: Deck.cpp Deck.h Card.h
	g++ -c Deck.cpp
	
Card.o: Card.cpp Card.h
	g++ -c Card.cpp
	
clean:
	rm -f *.o Decks_game
