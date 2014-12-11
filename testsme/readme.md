hur man bygger programmet
hur man kör programmet
lista över samtliga mål som redovisats med programmet
listar eventuella utökningar
övrig information av nytta
att fixa: Varför kollar vi bara om värdet är -400 i update
Defensiv programmering för att kolla indata (inte negativa värden)

tester: addforce är inte klart, kolla att macron funkar, testupdate kan krångla,



Nbody ver 1.337

Welcome to the Nbody Simulation Software("tm")!

Table of contents:
1. The Aim of Nbody
2. How to install and setup Nbody
3. How to run Nbody
4. Useful info
5. Version history

__________________________________________________________
1. The Aim of Nbody
__________________________________________________________
__________________________________________________________

In creating Nbody, we (the developers) wish to bring yet
another star to the sky of physics simulation software
as well as fulfilling the goals

A1
A3?
F13
H20
J26
O42
O43
R50

__________________________________________________________
2. How to install and setup Nbody
__________________________________________________________
__________________________________________________________

Firstly make sure you have gcc and make installed and put
yourself in the Nbody directory, then simply input

make install

and the rest will be handled by makescript (once again,
please make sure you have this wonderful tool installed)

__________________________________________________________
3. How to run Nbody
__________________________________________________________
__________________________________________________________

After successfully installing Nbody using the steps above,
simply input 

make run

when in the Nbody directory. Optionally, you can run
Nbody with custom parameters using the input

Nbody X Y

where 
X is the number of stars you wish to simulate and
Y is the amount of movements you wish each star to make

__________________________________________________________
4. Useful info
__________________________________________________________
__________________________________________________________

here we would post our expansions, IF WE HAD ANY

If you press and hold CTRL+ALT+DEL on a windows computer, 
there is a short window of time where your computer is
absolutely still.

According to the theory of relativity, every time you are
doing a pushup you are pushing the earth down.

__________________________________________________________
5. Version history
__________________________________________________________
__________________________________________________________

1.337 Current version, improved speed and physics

1.1 Slightly improved speed

1.0 Working version

0.37 Temporarily added recursive version of updateforces

0.13 