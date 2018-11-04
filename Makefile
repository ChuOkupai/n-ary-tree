CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

clean:
	rm -f *.o *.out

main.out: main.c node.c node.h
	$(CC) $(CFLAGS) $^ -o $@ -g

run: main.out
	./$<
