#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
//#include "gl.h" ?!?!

typedef struct edgedata {
  void* node;
  int line;
  int time;
  void* next;
} edgedata;

typedef struct node {
  char* name;
  void* edge;
  void* next;
} node;

node *root;
FILE* fp;
char inputFileName[] = "nat.txt";
char c;

node* getLastNode(node* start) {
  node* tempNode = start;
  while(tempNode->next != NULL) {
    tempNode = tempNode->next;
  }
  return tempNode;
}

edgedata* getLastEdge(edgedata* start) {
  edgedata* tempEdge = start;
  while(tempEdge->next != NULL) {
    tempEdge = tempEdge->next;
  }
  return tempEdge;
}

/**
   Creates a new node with a given name
   Sets first node created to root
   Links the node with previously added nodes
   @param name name of the node
   @return address to the new node
*/
node* newNode(char* name) {
  node* nodePointer = malloc(sizeof(node));
  //ibland kommer det ngt konstigt med name?! fixar det har
  int length = strlen(name) - 1;
  while(length != 0) {
    if(!isalpha(name[length]) && name[length] != ' ') {
      //printf("en fuling hittad: %c - på plats %d\n", name[length], length);
      name[length] = '\0';
    }
    length--;
  }
  
  nodePointer->name = name;
  if(root == NULL) {
    root = nodePointer;
  } else {
    getLastNode(root)->next = nodePointer;
  }
  return nodePointer;
}





node* findNode(node* root, char* name) {
  node* tempNode = root;
  while(tempNode != NULL) {
    // printf("jfr %s = %s\n", name, tempNode->name);
    if(!strcmp(name, tempNode->name)) {
      return tempNode;
    }
    tempNode = tempNode->next;
  }
  
  return NULL;
}


void removeNode(char* name) {
  node* nodetokill = findNode(root, name);
  if(nodetokill == root) {
    //if node is first
    root = nodetokill->next;
    free(nodetokill);
  } else if(nodetokill != NULL) {
    //find previous node
    node* prevNode = root;
    while(prevNode->next != nodetokill) {
      prevNode = prevNode->next;
    }
    //find next node
    node* nextNode = nodetokill->next;
    if (nodetokill->next == NULL) {
      //noden sist på listan. ta bara bort
      //ta bort alla edgedatan ocksa!
      prevNode->next = NULL;
      free(nodetokill);
    } else {
      //noden är omringad
      prevNode->next = nextNode;
      free(nodetokill);
    }
  } else {
    puts("node not found");
  }
}


void removeEdge(node* node1, char* name) {
  edgedata* edgetemp = node1->edge;
  node* nodeToKill = findNode(root, name);
  if(edgetemp != NULL) {
    while(edgetemp->node != nodeToKill) {
      edgetemp = edgetemp->next;
    }
    if(edgetemp->node == nodeToKill) {
      node1->edge = ((edgedata*) node1->edge)->next;
      free(edgetemp);
    }
  } else {
    puts("no edge found");
  }
}


/**
   Add a neighbor to a node
   @param node node to given edgedata
   @param line bus line
   @param time travel time to that stop
   @param busstop the neighbor
*/
void prependEdge(node* node, short line, short time, char* busstop) {
  edgedata* edgetemp = calloc(sizeof(edgedata), 1);
  edgetemp->node = findNode(root, busstop);
  edgetemp->line = line;
  edgetemp->time = time;

  if(node->edge == NULL) {
    node->edge = edgetemp;
  } else {
    edgedata* lastedge = getLastEdge(node->edge);
    lastedge->next = edgetemp;
  }
}

void initBusStops() {
  fp = fopen(inputFileName, "r");
  int step = 1;
  int lastCharWasComma = 0;
  
  char* step1 = malloc(sizeof(char)*5); //linje
  node* step2;
  node* step3;
  char* tempName = malloc(sizeof(char)*50);//name of bus stop
  char* step4 = malloc(sizeof(char)*5); //tid

  while(!feof(fp)) {
    c = fgetc(fp);
    
    if (c != ',' && !lastCharWasComma) {
        char buf[2];
        sprintf(buf, "%c", c);
        switch(step) 
          {
          case(1): strcat(step1, buf); break;
          case(2): strcat(tempName, buf); break;
          case(3): strcat(tempName, buf); break;
          case(4): strcat(step4, buf); break;
          }
      }
      
    if(c == ',') {
      if(step == 2 || step == 3) {


    
        if(findNode(root, tempName) == NULL) {

          //Try to add node
          char* finalName = calloc(sizeof(char)*strlen(tempName), 1);
          strcpy(finalName, tempName);
          
          switch(step) 
            {
            case(2): step2 = newNode(finalName); break;
            case(3): step3 = newNode(finalName); 
              //printf("step3 add!: %s\n", finalName);
              //printf("nyligen addad!: %s\n", getLastNode(root)->name);
              break;
            }
          //  printf("addad nod: %s\n", getLastNode(root)->name);
        } else {
          // printf("%s redan addad!\n", tempName);
          switch(step) 
            {
            case(2): step2 = findNode(root, tempName); break;
            case(3): step3 = findNode(root, tempName); break;
            }
        
        }

        tempName[0] = '\0';
      }
      step++;
      lastCharWasComma = 1;
    }
    else {
      lastCharWasComma = 0;
    }

    if (c == '\n') {
      //Add edge data
      //printf("%s, %s %d, %s, %s\n", step1, step2->name, strlen(step2->name), step3->name, step4);
      //kontrollera edgelistorna:
      
      prependEdge(step3, atoi(step1), atoi(step4), step2->name);
      prependEdge(step2, atoi(step1), atoi(step4), step3->name);
   
      step1[0] = '\0';
      step4[0] = '\0';
      step = 1;
    }
  }

  fclose(fp);
}

void shortestPath(node* root, char* from, char* to) {
  //kolla om de finns som edge och pa samma linje
  //i varje edge, kör hela funktionen
  //kolla om de är på samma busslinje
  node* fromNode = findNode(root, from);
  node* toNode = findNode(root, to);
  assert(fromNode != NULL);
  assert(toNode != NULL);

  
  puts("starts search...");
}


void printAllStops() {
  puts("_alla stop_");
  node* tempNode = root;
  while(tempNode != NULL) {
    char* thename = tempNode->name;
    printf("adr: %p, name: %s\n", tempNode, thename);
    edgedata* tempEdge = tempNode->edge;
    int i = 1;
    while(tempEdge != NULL) {
  
      printf("%d >%s\n", i, ((node*)(tempEdge->node))->name);
      tempEdge = tempEdge->next;
      i++;
      
    }
    tempNode = tempNode->next;
  }
}

int main()
{
  initBusStops();

  // removeNode("Centralstationen");
  // removeNode("Kalle Anka");
  //removeNode("Biomedicinskt centrum");
  //printAllStops();
  //  node* testrm = findNode(root, "Langvagen");
  //removeEdge(testrm, "Gottsundavagen");
  // removeEdge(testrm, "Cellovagen");
  printAllStops();

  // newNode("Biomedicinskt centrum");
  //printf("%p %p\n", findNode(root, "Biomedicinskt centrum"), findNode(root, "Akademiska sodra"));
  return 0;
}
