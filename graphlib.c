// funktioner
// inlï¿½sning frï¿½n fil; hur vet vi hur mÃ¥nga busshÃ¥llplatser/edges: lista Ã¶ver alla busshÃ¥lsplatser
// bussfunktioner; dvs getweight och getdata, freeedge( för att ta bort edge_data
// sï¿½kfunktion?
// nod innehåller: namn, edgedata->edge_data (busslinje, tid, hållplatsnamn)
// lista
// noder innehÃ¥ller lista med {busslinje, tid, hÃ¥llplatsnamn}
// hur rÃ¤kna grannar om trafik enkelriktad (lÃ¥gprio)
// behöver vi använda strcmp etc eller räcker det med att jämföra minnesaddresser? när man matar in en sträng kan man ändå ta ut innehållet ur addressen och jämföra...
// ha en stor lista med alla noder? skulle göra sökning otroligt mkt lättare... hur söka genom alla noder annars?
// koppling mellan inläsning och nodskapande
// ändra så att node->name inte är en char, utan en pekare till själva noden; annars måste jämföra på något annat sätt.
// borde egentligen skapa ett separat list-bibliotek som man kan inkludera, och implementera funktioner såsom find, exists etc
// vad ska connectnodes ta för data för tid och busslinje?
// fixa så att removenode söker igenom hela nätet efter referenser till noden
// ska hallplats vara en node* (alltså gå direkt till noden) eller en char* och gå till nodedata

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
  int linje;
  int tid;
  char* hallplats;   //ska peka på namnet i listan
} bussedgen;


typedef struct {
void* next;
bussedgen* current;
} list;

typedef struct {
  char* name;           //skall vara en pekare till nodename i nodedata i listlist
  list* grannar;
} node;

typedef struct {
void* next;
void* current;
} listlist;

typedef struct {
node* node;
char* nodename;
} nodedata;

node newNode(char* name, bussedgen* edgelist){
  node* pointer = malloc(sizeof(node));
  pointer->name = name;
   //kan behövas en slags konstruktor här, som bygger upp bussedgen
   /*
   pointer->bussedgen = constructList(edgelist) men då kommer det vanliga problemet med om vi redan mallocat edgelist hur vet vi hur stor den är


   */

  pointer->grannar->current = edgelist;
  return *pointer;
}


void connectNodes(node* node1, node* node2){
  //kolla om noderna finns i varandras listor (kÃ¤nner till varandra), om inte lï¿½gg till
  list* searchtemp = node1->grannar;
  list* listtemp;
  int inlist = 0;

  while(1

        //(searchtemp->next =/= NULL //funkar inte i codeblocks, vet inte varför

        ){
    if (searchtemp->current->hallplats == node2->name){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }

  //om namnet inte finns med så lägg till den
  if (inlist == 0){

      searchtemp->next = malloc(sizeof(list));
    list* listtemp = searchtemp->next;          //behövdes för att codeblocks var cp; testa bortkommenterade under
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    listtemp->current->hallplats = node2->name;
//      searchtemp->next->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
//      searchtemp->next->current->hallplats = node2->name;
    }



  //om namnet finns med, sök igenom node2s lista efter node1
  inlist = 0;
  searchtemp = node2->grannar;

  while(1

        //(searchtemp->next =/= NULL //funkar inte i codeblocks, vet inte varför

        ){
    if (searchtemp->current->hallplats == node1->name){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }
  //om namnet inte finns med så lägg till den
  if (inlist == 0){

    searchtemp->next = malloc(sizeof(list));
    listtemp = searchtemp->next;          //behövdes för att codeblocks var cp; testa bortkommenterade under
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    listtemp->current->hallplats = node1->name;
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

void removeNode(listlist* nodelist, node* node){ //listlist är en lista av alla noder, där nodens , node är noden som ska tas bort

  //kolla alla noder; ta bort noden frï¿½n allas listor och fria noden och edges
  //ta första ur nodelist, hitta node i dess nodelist,( länka över i listan, ta bort edgen till node, fria listan, fria edgen)
  //ta nästa ur nodelist, upprepa
  //när nodelist tom, fria och fria node; måste dessutom fria innehållet i edge

  //kolla om noden har några grannar; ska kolla från båda hållen, dvs söka igenom hela nätet?


listlist* searchtemp = nodelist;
node* looptemp = searchtemp->current;

    if(searchtemp->current == *void) {} //ska inte hända, så kanske onödigt

    if(searchtemp->next == *void) {} //detta är sista noden









  //för varje loop, hoppa till nästa listpost; sluta efter loopen när sista är void(stämmer med for-loopen?)
  //searchtemp pekar alltså på nodens lista med noder, som innehåller pekare till grannoderna;
  //hitta noden i grannodens lista
  //måste alltså kolla nästa nod i kedjan?

  // om noden är hittad, ta bort edgen, länka över, fria listan, edge
  if(searchtemp->next->current == node->name){

    removeEdge(searchtemp->next->current,searchtemp->next->current->edgelist);
    searchtemp->next = searchtemp->next->current->next;//kommer funka även om nästa post är slutet


  }

  free(node);
}

/*
edge* shortestPath(node from, node to){

  // vill ha två listor; en unvisited, en visited samt en variabel för varje nod, som är dess "avstånd"
  // behöver egentligen bara en lista, med unvisited?
  list* visited = ;
  list* unvisited = globalnodelist; //alla noder skall börja häri
  //alla noder skall ha en "oändlig" distance från start

  node* current = from;
  int startToHere = 0;

  //jämför avstånd till alla obesökta grannar från current, beräkna deras avstånd från start, och ge dem det lägsta om nuvarande är högre
  //om grannen är obesökt; beräkna avstånd från start;
  if(

){
    if(from->edgelist->edge_weight => *****LÄNGDVARIABEL*****
     ){
    ******LÄNGDVARIABEL********
      = (from->edgelist->edge_weight + startToHere)
      }

  }

  //ta bort noden från unvisited

  //om målnoden är besökt

  //ELLER om det minsta avståndet mellan de obesökta noderna är oändligt (alltså finns inga vägar dit från starten)
  //så avsluta

  //annars välj den obesökta noden med minst avstånd och börja om.


  /*djikstras algoritm:
    Wikipedia*/


//}
/*
void cleanup(){}//fundera på att adda; ta bort alla noder som inte sitter ihop med något?

void constructGraph(){

  //skapa alla noder som poster i en lista
}
*/


