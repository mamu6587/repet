N-body
======
Uppsala University
IOOPM 2014
Staffan Edstrom and Magnus Muhr

Description
-----------
N-body simulates how a number of stars interact with eachother in space 
according to the physical laws of the universe.


Compile the program
-------------------

Compile for benchmarking the star simulation without animation:
make starsim

Compile for animation:
make animate

Run the program
---------------

If no arguments are given to the program it runs with default values 200 bodies
and 1000 iterations

To run the program with default values:
./main

To run the program with custom values,
N and iter must be a positive integer:
./main [N number of bodies] [iter number of iterations]

To run the tests:
make runtest

Documentation
-------------

Doxygen generated manuals are found in refman.pdf

Achievements
------------

A1, F13, H20, J26, (I22, M36, M38)
