CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

clean:
	rm -f *.out

%.out: %.c node.c node.h
	$(CC) $(CFLAGS) $^ -o $@

run: main.out
	./$<