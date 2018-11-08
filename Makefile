CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

clean:
	rm -f *.o *.out

%.out: %.c node.c node.h
	$(CC) $(CFLAGS) $^ -o $@

main: main.out
	./$<

sample0: sample0.out
	./$<
