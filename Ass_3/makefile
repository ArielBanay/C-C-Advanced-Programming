PokemonsBattles: PokemonsBattleCenter.o BattleByCategory.o LinkedList.o MaxHeap.o Pokemon.o
	gcc PokemonsBattleCenter.o BattleByCategory.o LinkedList.o MaxHeap.o Pokemon.o -o PokemonsBattles

PokemonsBattleCenter.o: PokemonsBattleCenter.c BattleByCategory.h LinkedList.h MaxHeap.h Pokemon.h Defs.h
	gcc -c PokemonsBattleCenter.c

BattleByCategory.o: BattleByCategory.c BattleByCategory.h LinkedList.h MaxHeap.h Defs.h
	gcc -c BattleByCategory.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c

Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c

clean:
	rm -f *.o PokemonsBattles