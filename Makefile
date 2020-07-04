CFLAGS = -Wall -ansi -ggdb
CC = gcc
CLIBS = -lncurses

default: all

all: tetris

tetris: tetris.c init.o moving.o
	$(CC) -o tetris tetris.c init.o moving.o $(CFLAGS) $(CLIBS)

test: test.c init.o moving.o
	$(CC) -o test test.c init.o moving.o $(CFLAGS) $(CLIBS)

init.o: init.c
	$(CC) -c init.c $(CFLAGS) $(CLIBS)

moving.o: moving.c
	$(CC) -c moving.c $(CFLAGS) $(CLIBS)

purge:
	rm tetris *.o
