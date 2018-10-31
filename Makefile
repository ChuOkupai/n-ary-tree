CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

clean:
	rm -f *.o *.out

rpg.o: rpg.c rpg.h
	$(CC) $(CFLAGS) -c $< -o $@

main.out: main.c rpg.o rpg.h
	$(CC) $(CFLAGS) $^ -o $@ -g

run: main.out
	./$<
