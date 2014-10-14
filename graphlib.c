// funktioner
// inl�sning fr�n fil; hur vet vi hur många busshållplatser/edges: lista över alla busshålsplatser
// bussfunktioner; dvs getweight och getdata, freeedge( f�r att ta bort edge_data
// s�kfunktion?
// nod inneh�ller: namn, edgedata->edge_data (busslinje, tid, h�llplatsnamn)
// lista
// noder innehåller lista med {busslinje, tid, hållplatsnamn}
// hur räkna grannar om trafik enkelriktad (lågprio)
// beh�ver vi anv�nda strcmp etc eller r�cker det med att j�mf�ra minnesaddresser? n�r man matar in en str�ng kan man �nd� ta ut inneh�llet ur addressen och j�mf�ra...
// ha en stor lista med alla noder? skulle g�ra s�kning otroligt mkt l�ttare... hur s�ka genom alla noder annars?
// koppling mellan inl�sning och nodskapande
// �ndra s� att node->name inte �r en char, utan en pekare till sj�lva noden; annars m�ste j�mf�ra p� n�got annat s�tt.
// borde egentligen skapa ett separat list-bibliotek som man kan inkludera, och implementera funktioner s�som find, exists etc
// vad ska connectnodes ta f�r data f�r tid och busslinje?
// fixa s� att removenode s�ker igenom hela n�tet efter referenser till noden
// ska hallplats vara en node* (allts� g� direkt till noden) eller en char* och g� till nodedata

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
  int linje;
  int tid;
  char* hallplats;   //ska peka p� namnet i listan
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
   //kan beh�vas en slags konstruktor h�r, som bygger upp bussedgen
   /*
   pointer->bussedgen = constructList(edgelist) men d� kommer det vanliga problemet med om vi redan mallocat edgelist hur vet vi hur stor den �r


   */

  pointer->grannar->current = edgelist;
  return *pointer;
}


void connectNodes(node* node1, node* node2){
  //kolla om noderna finns i varandras listor (känner till varandra), om inte l�gg till
  list* searchtemp = node1->grannar;
  list* listtemp;
  int inlist = 0;

  while(1

        //(searchtemp->next =/= NULL //funkar inte i codeblocks, vet inte varf�r

        ){
    if (searchtemp->current->hallplats == node2->name){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }

  //om namnet inte finns med s� l�gg till den
  if (inlist == 0){

      searchtemp->next = malloc(sizeof(list));
    list* listtemp = searchtemp->next;          //beh�vdes f�r att codeblocks var cp; testa bortkommenterade under
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    listtemp->current->hallplats = node2->name;
//      searchtemp->next->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
//      searchtemp->next->current->hallplats = node2->name;
    }



  //om namnet finns med, s�k igenom node2s lista efter node1
  inlist = 0;
  searchtemp = node2->grannar;

  while(1

        //(searchtemp->next =/= NULL //funkar inte i codeblocks, vet inte varf�r

        ){
    if (searchtemp->current->hallplats == node1->name){
      inlist = 1;
    }
    searchtemp = searchtemp->next;
  }
  //om namnet inte finns med s� l�gg till den
  if (inlist == 0){

    searchtemp->next = malloc(sizeof(list));
    listtemp = searchtemp->next;          //beh�vdes f�r att codeblocks var cp; testa bortkommenterade under
    listtemp->current = malloc(sizeof(bussedgen)+sizeof(char)*(strlen(node2->name)));
    listtemp->current->hallplats = node1->name;
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

void removeNode(listlist* nodelist, node* node){ //listlist �r en lista av alla noder, d�r nodens , node �r noden som ska tas bort

  //kolla alla noder; ta bort noden fr�n allas listor och fria noden och edges
  //ta f�rsta ur nodelist, hitta node i dess nodelist,( l�nka �ver i listan, ta bort edgen till node, fria listan, fria edgen)
  //ta n�sta ur nodelist, upprepa
  //n�r nodelist tom, fria och fria node; m�ste dessutom fria inneh�llet i edge

  //kolla om noden har n�gra grannar; ska kolla fr�n b�da h�llen, dvs s�ka igenom hela n�tet?


listlist* searchtemp = nodelist;
node* looptemp = searchtemp->current;

    if(searchtemp->current == *void) {} //ska inte h�nda, s� kanske on�digt

    if(searchtemp->next == *void) {} //detta �r sista noden









  //f�r varje loop, hoppa till n�sta listpost; sluta efter loopen n�r sista �r void(st�mmer med for-loopen?)
  //searchtemp pekar allts� p� nodens lista med noder, som inneh�ller pekare till grannoderna;
  //hitta noden i grannodens lista
  //m�ste allts� kolla n�sta nod i kedjan?

  // om noden �r hittad, ta bort edgen, l�nka �ver, fria listan, edge
  if(searchtemp->next->current == node->name){

    removeEdge(searchtemp->next->current,searchtemp->next->current->edgelist);
    searchtemp->next = searchtemp->next->current->next;//kommer funka �ven om n�sta post �r slutet


  }

  free(node);
}

/*
edge* shortestPath(node from, node to){

  // vill ha tv� listor; en unvisited, en visited samt en variabel f�r varje nod, som �r dess "avst�nd"
  // beh�ver egentligen bara en lista, med unvisited?
  list* visited = ;
  list* unvisited = globalnodelist; //alla noder skall b�rja h�ri
  //alla noder skall ha en "o�ndlig" distance fr�n start

  node* current = from;
  int startToHere = 0;

  //j�mf�r avst�nd till alla obes�kta grannar fr�n current, ber�kna deras avst�nd fr�n start, och ge dem det l�gsta om nuvarande �r h�gre
  //om grannen �r obes�kt; ber�kna avst�nd fr�n start;
  if(

){
    if(from->edgelist->edge_weight => *****L�NGDVARIABEL*****
     ){
    ******L�NGDVARIABEL********
      = (from->edgelist->edge_weight + startToHere)
      }

  }

  //ta bort noden fr�n unvisited

  //om m�lnoden �r bes�kt

  //ELLER om det minsta avst�ndet mellan de obes�kta noderna �r o�ndligt (allts� finns inga v�gar dit fr�n starten)
  //s� avsluta

  //annars v�lj den obes�kta noden med minst avst�nd och b�rja om.


  /*djikstras algoritm:
    Wikipedia*/


//}
/*
void cleanup(){}//fundera p� att adda; ta bort alla noder som inte sitter ihop med n�got?

void constructGraph(){

  //skapa alla noder som poster i en lista
}
*/


