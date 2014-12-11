# Make animate to show a nice window
# Make starsim to only benchmark
test:	./testsme/nbodyUnittest.c main-iter.c
	gcc -std=c99 -DTEST -lcunit -lm -ggdb -o tests main-iter.c

starsim:
	gcc -std=c99 -DRUN main-iter.c -o main -lm

animate:
	gcc -std=c99 -DANIMATE -DRUN main-iter.c -o main -lm -lX11

run:
	./main

runtest: test
	./tests