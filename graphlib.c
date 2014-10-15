// funktioner
// inlï¿½sning frï¿½n fil; hur vet vi hur mÃ¥nga busshÃ¥llplatser/edges: lista Ã¶ver alla busshÃ¥lsplatser
// bussfunktioner; dvs getweight och getdata, freeedge( för att ta bort edge_data
// hur rÃ¤kna grannar om trafik enkelriktad (lÃ¥gprio)
// ha en stor lista med alla noder? skulle göra sökning otroligt mkt lättare... hur söka genom alla noder annars?
// koppling mellan inläsning och nodskapande
// borde egentligen skapa ett separat list-bibliotek som man kan inkludera, och implementera funktioner såsom find, exists etc
// vad ska connectnodes ta för data för tid och busslinje?
// glöm inte att fria listan varje gång man friar edge eller node
// testa alla, skriv tester
#include <string.h> //EV ONÖDIG
#include <stdlib.h>


/* //generell
   typedef struct {
   void* edge_weight;
   void* edge_data;
   } edgedata;
*/

//glöm inte att ändra när ska göras generellt

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

void prependEdge(node* node, short linje, short tid, char* hallplats){//lägger till edge i början på node's edgelist
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
  //kolla om noderna finns i varandras listor (kÃ¤nner till varandra), om inte lï¿½gg till
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

  //om namnet inte finns med så lägg till den
  if (inlist == 0){

    searchtemp->next = malloc(sizeof(list));
    listtemp = searchtemp->next;
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name))); //kolla igenom
    edgetemp->hallplats = node2;
    //      searchtemp->next->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    //      searchtemp->next->current->hallplats = node2->name;
  }



  //om namnet finns med, sök igenom node2s lista efter node1
  inlist = 0;
  searchtemp = node2->grannar;
  edgetemp = searchtemp->current;

  while(searchtemp->next != NULL){
    if (edgetemp->hallplats == node1){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }
  //om namnet inte finns med så lägg till den
  if (inlist == 0){

    searchtemp->next = malloc(sizeof(list));
    listtemp = searchtemp->next;          //behövdes för att codeblocks var cp; testa bortkommenterade under
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    edgetemp->hallplats = node1;
    //      searchtemp->next->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    //      searchtemp->next->current->hallplats = node2->name;
  }
}

/*
  void removeEdge(node node, edge edge){
  //ta bort kopplingen mellan 2 noder och fria, behöver därför veta till vilken nod edgen ska leda.

  free(edge);
  }
*/

void removeNode(list* nodelist, list* toRemove){

  //list är en lista av alla noder, node är noden som ska tas bort
  //kolla alla noder; ta bort noden frï¿½n allas listor och fria noden och edges
  //ta första ur nodelist, hitta node i dess nodelist,( länka över i listan, ta bort edgen till node, fria listan, fria edgen)
  //ta nästa ur nodelist, upprepa
  //när nodelist tom, fria och fria node; måste dessutom fria innehållet i edge
  //kolla om noden har några grannar; ska kolla från båda hållen, dvs söka igenom hela nätet?

  node* nodetokill = toRemove->current; //att kolla mot
  list* searchtemp = nodelist;
  node* nodepointer = searchtemp->current;  // noden som söks igenom
  list* prevtemp = NULL; // förra genomsökta, att använda för att länka över.

  while(nodepointer != NULL){   //tills vi är i slutet av nodelist
  if(nodepointer->name == toRemove->current) { //om det är noden, länka listan över den...
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
          //för varje loop, hoppa till nästa listpost; sluta efter loopen när sista är void(stämmer med for-loopen?)
          //searchtemp pekar alltså på nodens lista med noder, som innehåller pekare till grannoderna;
          //hitta noden i grannodens lista
          //måste alltså kolla nästa nod i kedjan?

          free(nodetokill);   //fria noden
          free(toRemove);   //fria nodens listpost
        }


          list* shortestPath(list* nodelist, char* from, char* to){ //kommer bygga upp och returnera en lista, där varje post är edgen som ska tas från from för att komma till to

          // vill ha två listor; en unvisited, en visited samt en variabel för varje nod, som är dess "avstånd"
          // behöver egentligen bara en lista, med unvisited?
          // gör en int array med tre inlägg; node* (pekare till noden, används som ID), visited (0 eller 1), tentative distance (börjar på -1)
          int numberOfNodes = 0;
          list* listtemp = nodelist;
          while(nodelist != NULL){
            listtemp = listtemp->next;
            numberOfNodes++;
          }
        int* start;
        node* nodeAddress;
          int listnodes[numberOfNodes][3]; //alla noder skall börja häri
                                    //alla noder skall ha -1 distance från start
        for(int i = 0;i < numberOfNodes;i++){//initialisera arrayen till (nod*, 0, if(from){0} else -1)

        //listnodes[i][0] = ((int)*nodeAddress); //Kan behöva lösas med lite god pekararitmetik;
                listnodes[i][1] = 0;
                            if(nodeAddress->name == from){ //hur få tag i noden här?
                            listnodes[i][2] = 0;
                            start = listnodes[i];
                            }
                        listnodes[i][2] = -1;
        }

            nodeAddress = &start;
          int* currentnode = start;
          int startToHere = 0;

          //jämför avstånd till alla obesökta grannar från current, beräkna deras avstånd från start, och ge dem det lägsta om nuvarande är högre
          //om grannen är obesökt; beräkna avstånd från start;
          //ta ut en granne
          list* edgelistlooptemp = nodeAddress->grannar;
          bussedgen* edgeaccesstemp = edgelistlooptemp->current;
          while (edgelistlooptemp->next != NULL){ //bättre att loopa på denna då den är kortare
          for(int i = 0; i < numberOfNodes; i++);if(listnodes[i][0] == &

          ){
          if(from->edgelist->edge_weight => *****LÄNGDVARIABEL*****
          ){
          ******LÄNGDVARIABEL********
          = (from->edgelist->edge_weight + startToHere)
          }

          }
          }
          //ta bort noden från unvisited

          //om målnoden är besökt

          //ELLER om det minsta avståndet mellan de obesökta noderna är oändligt (alltså finns inga vägar dit från starten)
          //så avsluta

          //annars välj den obesökta noden med minst avstånd och börja om.

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
