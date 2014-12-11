# Make animate to show a nice window
# Make starsim to only benchmark
test:
	gcc -std=c99 main-tests.c

starsim:
	gcc -std=c99 main-iter.c -o main -lm

animate:
	gcc -std=c99 -DANIMATE main-iter.c -o main -lm -lX11

run:
	./main