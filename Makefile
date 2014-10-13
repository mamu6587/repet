CC = gcc
Cflags = -ggdb -Wall -std=c99 -o
test: test.c
	$(CC) $(Cflags) test test.c

main: main.c
	$(CC) $(Cflags) main main.c

animate: main.c
		gcc -Wall -ggdb -std=c99 -DANIMATE main.c -o main -lm -lX11

rec: main-rec.c
		gcc -Wall -ggdb -std=c99 -DANIMATE main-rec.c -o main -lm -lX11

iter: main-iter.c
		gcc -Wall -ggdb -std=c99 -DANIMATE -pg  main-iter.c -o main -lm -lX11

prof: main-profil.c
		gcc -Wall -ggdb -std=c99 -DANIMATE -pg  main-profil.c -o mainprof -lm -lX11

run:
	main

buss: graphlib.c
	$(CC) $(Cflags) graphlib graphlib.c

prov: kodprovskladd.c
	$(CC) $(Cflags) kodprov kodprovskladd.c