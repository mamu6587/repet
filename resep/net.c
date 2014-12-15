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

node* root;
node* visited;
FILE* fp;
char inputFileName[] = "nat.txt";
char c;

node* getLastNode(node* start) {
  node* tempNode = start;
  //printf("den sista noden: %s\n", tempNode->name);
  //printf("den sista pekaren: %p\n", tempNode->next);
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
   Sets first node created to root list
   Links the node with previously added nodes
   @param name name of the node
   @return address to the new node
*/
node* newNode(node** list, char* name) {

  char* finalName = calloc(sizeof(char)*strlen(name), 1);
  strcpy(finalName, name);
          
  node* nodePointer = malloc(sizeof(node));
  //ibland kommer det ngt konstigt med name?! fixar det har
  int length = strlen(finalName) - 1;
  while(length != 0) {
    if(!isalpha(finalName[length]) && finalName[length] != ' ') {
      //printf("en fuling hittad: %c - på plats %d\n", finalName[length], length);
      finalName[length] = '\0';
    }
    length--;
  }
 
  nodePointer->name = finalName;
  
  if(*list == NULL) {
    //puts("detta blir roten i listan\n");
    *list = nodePointer;
  } else {
    getLastNode(*list)->next = nodePointer;
  }
  nodePointer->next = NULL;
  //printf("nyligen addad!: %s\n", getLastNode(*list)->name);
  return nodePointer;
}





node* findNode(node* list, char* name) {
  node* tempNode = list;

  while(tempNode != NULL) {
    // printf("jfr %s = %s\n", name, tempNode->name);
    if(!strcmp(name, tempNode->name)) {
      return tempNode;
    }
    tempNode = tempNode->next;
  }
  
  
  return NULL;
}


void removeNode(node* list, char* name) {
  node* nodetokill = findNode(list, name);
  if(nodetokill == list) {
    //if node is first
    list = nodetokill->next;
    free(nodetokill);
  } else if(nodetokill != NULL) {
    //find previous node
    node* prevNode = list;
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

          switch(step) 
            {
            case(2): step2 = newNode(&root, tempName); break;
            case(3): step3 = newNode(&root, tempName); 
              //printf("step3 add!: %s\n", finalName);
              
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

void possiblePaths(char* from, char* to) {
  //kolla om de finns som edge och pa samma linje
  //i varje edge, kör hela funktionen
  //kolla om de är på samma busslinje
  char* tempName = malloc(sizeof(char)*50);//name of bus stop
  node* fromNode = findNode(root, from);
  node* toNode = findNode(root, to);
  assert(fromNode != NULL);
  assert(toNode != NULL);
  
  edgedata* tempEdge = fromNode->edge;
    strcpy(tempName, fromNode->name); 

    while(tempEdge != NULL) {
      node* visitedList = NULL;
      newNode(&visitedList, fromNode->name);
      node* edgeNode = ((node*) tempEdge->node);
      //   printf("visited list star pa: %p\n", visitedList);
    /*if(fromNode == toNode) {
      //printa path o sdnt
      printf("found it efter ett steg");
      return;
      }*/
    
      node* secondNode = newNode(&visitedList, edgeNode->name);
      // printf("visited list nxt star pa: %p\n", visitedList->next);
      searchPath(visitedList, secondNode, toNode, tempEdge->line);
      
    tempEdge = tempEdge->next;
  }
  free(tempName);
  //puts("starts search...");
}


void printNodeList(int viewConnections, node* list) {
  puts("_alla stop_");
  node* tempNode = list;
  if(tempNode == NULL) {
    puts("omg! no stops added!");
  }
  while(tempNode != NULL) {
    // puts("this name crashes it!");
    // printf("this name crashes it! %s \n", tempNode->name);
    char* thename = tempNode->name;
    printf("adr: %p, nxt: %p, name: %s\n", tempNode, tempNode->next, thename);
    if(viewConnections == 1) {
      edgedata* tempEdge = tempNode->edge;
      int i = 1;
      while(tempEdge != NULL) {
        
        printf("%d >%s line: %d\n", i, ((node*)(tempEdge->node))->name, tempEdge->line);
        tempEdge = tempEdge->next;
        i++;
        
      }
    }
    tempNode = tempNode->next;
  }
}

void printTravelPath(node* list, int busline) {
  printf("\n -- Possible path by bus %d:\n", busline);
  node* tempNode = list;
  int totaltime = 0;
  int time = 0;
  while(tempNode != NULL) {
    //get time from here to next
    node* rootNode = findNode(root, tempNode->name);
    edgedata* tempEdge = rootNode->edge;

    if(tempNode->next != NULL) {
      while(tempEdge != NULL) {

        node* nextRootNode = findNode(root, ((node*)(tempNode->next))->name);
        if(tempEdge->node == nextRootNode) {
          time = tempEdge->time;
          totaltime += time;
        }
        tempEdge = tempEdge->next;
      }

      printf("%s \t %d mins\n", tempNode->name, time);
    } else {
      printf("%s\n", tempNode->name);
    }
    tempNode = tempNode->next;
  }
  puts("--------------------");
  printf("total time: %d mins\n", totaltime);
 
}

void searchPath(node* visitedList, node* current, node* to, int busline) {
  edgedata* tempEdge = findNode(root, current->name)->edge;
  char* tempName = malloc(sizeof(char)*50);//name of bus stop
  // printf("riding from %p %s, on line %d\n", visitedList, current->name, busline);
  while(tempEdge != NULL) {
    node* edgeNode = tempEdge->node;
    if(findNode(visitedList, edgeNode->name) == NULL) {
      //printf("en mojilg resvag: %s, %p\n", edgeNode->name, findNode(visitedList, edgeNode->name));

      //kontrollera om samma busslinje
      if(tempEdge->line == busline) {
        //nod kopplad till denna edge
        node* edgeNode = tempEdge->node;    
        if(edgeNode == to) {
          strcpy(tempName, edgeNode->name);
          newNode(&visitedList, tempName);
          // printf("reached goal %p %s Bus line: %d!\n", to, to->name, busline);
          //printa hela listan da
          printTravelPath(visitedList, busline);
          //printNodeList(0, visitedList);
        } else {
          strcpy(tempName, edgeNode->name);
          node* searchThisNode = newNode(&visitedList, tempName);

          searchPath(visitedList, searchThisNode, to, tempEdge->line);
        }
      }
    }
    
    tempEdge = tempEdge->next;
   }
  //printNodeList(0, visitedList);
  //free(visitedList);
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
 
  
  printNodeList(1, root);
 
  possiblePaths("Centralstationen", "Cellovagen");
  
  
  
  
 
  // printNodeList(0, visited);
  
/*node* tempNode = visited;
  while(tempNode->next != NULL) {
    puts("hittade en nod\n");
    tempNode = tempNode->next;
    }*/


  // newNode("Biomedicinskt centrum");
  //printf("%p %p\n", findNode(root, "Biomedicinskt centrum"), findNode(root, "Akademiska sodra"));
  return 0;
}
