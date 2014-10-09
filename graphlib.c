// funktioner
// inl�sning fr�n fil; hur vet vi hur många busshållplatser/edges: lista över alla busshålsplatser
// bussfunktioner; dvs getweight och getdata
// s�kfunktion?
// lista
// noder innehåller lista med {busslinje, tid, hållplatsnamn}
// hur räkna grannar om trafik enkelriktad (lågprio)



typedef struct {
  void* edge_weight;
  void* edge_data;
} edgedata;


typedef struct {
  char* name;
  edgedata* edgelist;
} node;

typedef struct {
  
  void* busslinje;
  void* hållplats;
  
} bussedgen;

typedef struct {
  void* current;
  void* nextlist
} listlist;

  node* newNode(char* name, edgedata* edgelist){
  node =  malloc(sizeof(node));
  node->name = name;
  node->edgelist = edgelist;
  return node;
}




void connectNodes(node node1, node node2){
  //kolla om noderna finns i varandras listor (känner till varandra), om inte l�gg till
  searchtemp = 

    //for(PLACEHOLDER searchtemp = node1->nodelist;searchtemp =/= void*; searchtemp = node1->nodelist->next;){}
  while(searchtemp =/= void*){
    if (searchtemp != node2->name){
      searchtemp = node1->nodelist->next;
    }
  }
 
  //kolla node2 nodelist
  while(searchtemp =/= void*){
    
  }
  // whil
}

void removeNode(node node){
  //kolla alla noder; ta bort noden fr�n allas listor och fria noden och edges

  free(node);
}

void removeEdge(edge edge){
  //ta bort kopplingen mellan 2 noder och fria
  
  free(edge);
}

edge* shortestPath(){

  /*djikstras algoritm:
    Wikipedia*/  
   
   
}
