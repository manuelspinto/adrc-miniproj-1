CC=gcc
CFLAGS=-g -c -Wall -ansi -pedantic -pg
LIBS=-lm

default: add2nh

add2nh: tree.o
	$(CC) -o add2nh tree.o $(LIBS) -pg

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) tree.c

clean::
	rm -f *.o core a.out graph *~
