CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

clean:
	rm -f *.o *.out

node.o:	node.c node.h
	$(CC) $(CFLAGS) -c $< -o $@

%.out: %.c node.o
	$(CC) $(CFLAGS) $^ -o $@

run: main.out
	./$<

loadTree: loadTree.out
	./$<