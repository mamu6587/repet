CC = gcc
CFLAGS = -w -std=c99 -ggdb

all: net graphlib
	$(CC) -o main net.o graphlib.o

net: net.c
	$(CC) $(CFLAGS) net.c -c

graphlib: graphlib.c
	$(CC) $(CFLAGS) graphlib.c -c

