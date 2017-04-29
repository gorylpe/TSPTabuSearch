CC=gcc
CFLAGS=-O3 -std=c99
LIBS=-lm
OBJS=main.o startingcycle.o swap2opt.o tabulist.o tabusearch.o util.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@
clean:
	rm -f *.o
