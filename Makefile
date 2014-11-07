all: makenet

makenet: network.c
	gcc -Wall -ggdb -std=c99 -o net network.c