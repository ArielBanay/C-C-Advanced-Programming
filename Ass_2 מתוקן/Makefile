Pokedex: Pokedex.o Pokemon.o
	gcc Pokedex.o Pokemon.o -o Pokedex

Pokedex.o: Pokedex.c Pokemon.h Defs.h
	gcc -c Pokedex.c

Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c

clean:
	rm -f *.o Pokedex