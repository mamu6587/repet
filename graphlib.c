
// funktioner
// inl�sning fr�n fil
// bussfunktioner


typedef struct {
  void* edge_weight;
  void* edge_data;   
} edgedata;


typedef struct {
  char* name;
  edgedata* edgelist;
  //node* nodelist;
} node;



node* newNode(char* name, edgedata* edgelist, node* nodelist){
  node =  malloc(sizeof(node));
  
}

void connectNodes(node node1, node node2){
  //kolla om noden finns i b�da nodernas listor, om inte l�gg till
}

void removeNode(node node){
  
}

void removeEdge(edge edge){
}

edge* shortestPath

