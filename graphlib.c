// funktioner
// inl�sning fr�n fil; hur vet vi hur många busshållplatser/edges: lista över alla busshålsplatser
// bussfunktioner; dvs getweight och getdata, freeedge( f�r att ta bort edge_data
// hur räkna grannar om trafik enkelriktad (lågprio)
// ha en stor lista med alla noder? skulle g�ra s�kning otroligt mkt l�ttare... hur s�ka genom alla noder annars?
// koppling mellan inl�sning och nodskapande
// borde egentligen skapa ett separat list-bibliotek som man kan inkludera, och implementera funktioner s�som find, exists etc
// vad ska connectnodes ta f�r data f�r tid och busslinje?
// gl�m inte att fria listan varje g�ng man friar edge eller node
// testa alla, skriv tester
#include <string.h> //EV ON�DIG
#include <stdlib.h>


/* //generell
   typedef struct {
   void* edge_weight;
   void* edge_data;
   } edgedata;
*/

//gl�m inte att �ndra n�r ska g�ras generellt

typedef struct {
  void* current;
  void* next;
} list;

typedef struct {
  char* name;
  void* grannar;     //ska vara en lista av edges
} node;

typedef struct {
  short linje;
  short tid;
  node* hallplats;
} bussedgen;



node* newNode(char* name){ //skapar en node med name name, returnerar en pekare till noden.
  node* nodepointer = malloc(sizeof(node));
  nodepointer->name = name;

  list* listpointer = malloc(sizeof(list));
  listpointer->current = nodepointer;

  return nodepointer;
}

void prependEdge(node* node, short linje, short tid, char* hallplats){//l�gger till edge i b�rjan p� node's edgelist
  list* first = node->grannar;

 list* temp = malloc(sizeof(list));
 temp->next = first;
 node->grannar = temp;
 bussedgen* edgetemp = malloc(sizeof(bussedgen));
 temp->current = edgetemp;
  edgetemp->hallplats = hallplats;
  edgetemp->linje = linje;
  edgetemp->tid = tid;
}


void connectNodes(node* node1, node* node2){
  //kolla om noderna finns i varandras listor (känner till varandra), om inte l�gg till
  list* searchtemp = node1->grannar;
  bussedgen* edgetemp;
  list* listtemp;
  int inlist = 0;

  while(searchtemp->next != NULL){
    edgetemp = searchtemp->current;
    if (edgetemp->hallplats == node2){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }

  //om namnet inte finns med s� l�gg till den
  if (inlist == 0){

    searchtemp->next = malloc(sizeof(list));
    listtemp = searchtemp->next;
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name))); //kolla igenom
    edgetemp->hallplats = node2;
    //      searchtemp->next->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    //      searchtemp->next->current->hallplats = node2->name;
  }



  //om namnet finns med, s�k igenom node2s lista efter node1
  inlist = 0;
  searchtemp = node2->grannar;
  edgetemp = searchtemp->current;

  while(searchtemp->next != NULL){
    if (edgetemp->hallplats == node1){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }
  //om namnet inte finns med s� l�gg till den
  if (inlist == 0){

    searchtemp->next = malloc(sizeof(list));
    listtemp = searchtemp->next;          //beh�vdes f�r att codeblocks var cp; testa bortkommenterade under
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    edgetemp->hallplats = node1;
    //      searchtemp->next->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    //      searchtemp->next->current->hallplats = node2->name;
  }
}

/*
  void removeEdge(node node, edge edge){
  //ta bort kopplingen mellan 2 noder och fria, beh�ver d�rf�r veta till vilken nod edgen ska leda.

  free(edge);
  }
*/

void removeNode(list* nodelist, list* toRemove){

  //list �r en lista av alla noder, node �r noden som ska tas bort
  //kolla alla noder; ta bort noden fr�n allas listor och fria noden och edges
  //ta f�rsta ur nodelist, hitta node i dess nodelist,( l�nka �ver i listan, ta bort edgen till node, fria listan, fria edgen)
  //ta n�sta ur nodelist, upprepa
  //n�r nodelist tom, fria och fria node; m�ste dessutom fria inneh�llet i edge
  //kolla om noden har n�gra grannar; ska kolla fr�n b�da h�llen, dvs s�ka igenom hela n�tet?

  node* nodetokill = toRemove->current; //att kolla mot
  list* searchtemp = nodelist;
  node* nodepointer = searchtemp->current;  // noden som s�ks igenom
  list* prevtemp = NULL; // f�rra genoms�kta, att anv�nda f�r att l�nka �ver.

  while(nodepointer != NULL){   //tills vi �r i slutet av nodelist
  if(nodepointer->name == toRemove->current) { //om det �r noden, l�nka listan �ver den...
        prevtemp->next = searchtemp->next;
  }
  list* grannarcurrent = nodepointer->grannar;
  bussedgen* edgepointer = grannarcurrent->current;
  list* grannarprev = NULL;

    while(grannarcurrent != NULL){
    if(nodetokill == edgepointer->hallplats){
            grannarprev->next = grannarcurrent->next;
        grannarprev = grannarcurrent;
        grannarcurrent = grannarcurrent->next;
        free(edgepointer);
        free(grannarcurrent);
        }
        grannarprev = grannarcurrent;
        grannarcurrent = grannarcurrent->next;
    }
  prevtemp = searchtemp;
  searchtemp = searchtemp->next;
  }
          //f�r varje loop, hoppa till n�sta listpost; sluta efter loopen n�r sista �r void(st�mmer med for-loopen?)
          //searchtemp pekar allts� p� nodens lista med noder, som inneh�ller pekare till grannoderna;
          //hitta noden i grannodens lista
          //m�ste allts� kolla n�sta nod i kedjan?

          free(nodetokill);   //fria noden
          free(toRemove);   //fria nodens listpost
        }


          list* shortestPath(list* nodelist, char* from, char* to){ //kommer bygga upp och returnera en lista, d�r varje post �r edgen som ska tas fr�n from f�r att komma till to

          // vill ha tv� listor; en unvisited, en visited samt en variabel f�r varje nod, som �r dess "avst�nd"
          // beh�ver egentligen bara en lista, med unvisited?
          // g�r en int array med tre inl�gg; node* (pekare till noden, anv�nds som ID), visited (0 eller 1), tentative distance (b�rjar p� -1)
          int numberOfNodes = 0;
          list* listtemp = nodelist;
          while(nodelist != NULL){
            listtemp = listtemp->next;
            numberOfNodes++;
          }
        int* start;
        node* nodeAddress;
          int listnodes[numberOfNodes][3]; //alla noder skall b�rja h�ri
                                    //alla noder skall ha -1 distance fr�n start
        for(int i = 0;i < numberOfNodes;i++){//initialisera arrayen till (nod*, 0, if(from){0} else -1)

        //listnodes[i][0] = ((int)*nodeAddress); //Kan beh�va l�sas med lite god pekararitmetik;
                listnodes[i][1] = 0;
                            if(nodeAddress->name == from){ //hur f� tag i noden h�r?
                            listnodes[i][2] = 0;
                            start = listnodes[i];
                            }
                        listnodes[i][2] = -1;
        }

            nodeAddress = &start;
          int* currentnode = start;
          int startToHere = 0;

          //j�mf�r avst�nd till alla obes�kta grannar fr�n current, ber�kna deras avst�nd fr�n start, och ge dem det l�gsta om nuvarande �r h�gre
          //om grannen �r obes�kt; ber�kna avst�nd fr�n start;
          //ta ut en granne
          list* edgelistlooptemp = nodeAddress->grannar;
          bussedgen* edgeaccesstemp = edgelistlooptemp->current;
          while (edgelistlooptemp->next != NULL){ //b�ttre att loopa p� denna d� den �r kortare
          for(int i = 0; i < numberOfNodes; i++);if(listnodes[i][0] == &

          ){
          if(from->edgelist->edge_weight => *****L�NGDVARIABEL*****
          ){
          ******L�NGDVARIABEL********
          = (from->edgelist->edge_weight + startToHere)
          }

          }
          }
          //ta bort noden fr�n unvisited

          //om m�lnoden �r bes�kt

          //ELLER om det minsta avst�ndet mellan de obes�kta noderna �r o�ndligt (allts� finns inga v�gar dit fr�n starten)
          //s� avsluta

          //annars v�lj den obes�kta noden med minst avst�nd och b�rja om.

/*
          djikstras algoritm:
          Wikipedia


        //}

          void constructGraph(){
          //skapa alla noder som poster i en lista
          }
        */

int main(){
  return 0;
}
