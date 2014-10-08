CC=gcc
CFLAGS=-g -c -Wall -ansi -pedantic
LIBS=-lm

default: graph

graph: tree.o
	$(CC) -o graph tree.o $(LIBS)

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) tree.c

clean::
	rm -f *.o core a.out graph *~
