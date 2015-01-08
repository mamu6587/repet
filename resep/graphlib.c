#include <stdlib.h>
#include <stdio.h>
#include "graphlib.h"

/**
 * @file graphlib.c
 * @author Staffan Edstrom, Magnus Muhr
 */

node* root;

/**
  Gets the last node of a node list
  @param start of linked node list
  @return last node of list
 */
node* getLastNode(node* start) {
  node* tempNode = start;
  while(tempNode->next != NULL) {
    tempNode = tempNode->next;
  }     
  return tempNode;
}


/**
   Gets the last edgedata of an edge list
   @param start start of a linked list
   @return last edgedata of list
 */
edgedata* getLastEdge(edgedata* start) {
  edgedata* tempEdge = start;
  while(tempEdge->next != NULL) {
    tempEdge = tempEdge->next;
  }
  return tempEdge;
}

/**
   Creates a new node with a given name
   Adds node at end of linked list
   @param list list to add a node
   @param name name of the node
   @return address to the new node
*/
node* newNode(node** list, char* name) {

  char* finalName = calloc(sizeof(char)*strlen(name), 1);
  strcpy(finalName, name);
          
  node* nodePointer = malloc(sizeof(node));
  //ibland kommer det ngt konstigt med name. fixar det har
  int length = strlen(finalName) - 1;
  while(length != 0) {
    if(!isalpha(finalName[length]) && finalName[length] != ' ') {
      //printf("en fuling hittad: %c - på plats %d\n", finalName[length], length);
      if(finalName[length] != '/' && 
         finalName[length] != '-') {
        finalName[length] = '\0';
      }
    }
    length--;
  }
 
  nodePointer->name = finalName;
  
  if(*list == NULL) {
    //detta blir roten i listan
    *list = nodePointer;
  } else {
    getLastNode(*list)->next = nodePointer;
  }
  nodePointer->next = NULL;
  //nyligen addad
  return nodePointer;
}

/**
   Finds a node in a node list
   @param list search this list of nodes
   @param name find node with this name
   @return address of found node if found, else NULL
 */
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

/**
   Tries to remove a node from a node list
   @param list list of nodes
   @param name remove node with this name
 */
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



/**
   Tries to remove an edgedata from a node
   @param node1 node to search for edges
   @param name remove edgedata with this name
*/
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
void appendEdge(node* node, short line, short time, char* busstop) {
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

/**
   Add a time when a bus leaves
   @param busline busline to add time to
   @param hour hour when bus leaves
   @param min minute when the bus leaves
 */
void addTime(busstart* busline, int hour, int min) {
  edgetime* newTime = malloc(sizeof(edgetime));
  newTime->hours = hour;
  newTime->minutes = min;
  newTime->next = NULL;
  if(busline->times != NULL) {
    edgetime* tempTime = busline->times;
    while(tempTime->next != NULL) {
      tempTime = tempTime->next;
    }
    tempTime->next = newTime;
  } else {
    busline->times = newTime;
  }
}


/**
   Add a time when a bus leaves the starting station
   @param node station to add time to
   @param busline busline to add time to
   @param hour hour when bus leaves
   @param min minute when the bus leaves
 */
void addStartTime(node* node, int line, int hour, int min) {
  int found = 0;
  busstart* tempBusstart = node->edge;
  while(tempBusstart != NULL) {
    if(tempBusstart->line == line) {
      found = 1;
    }
    tempBusstart = tempBusstart->next;
  }
  //if found: lagg till starttime
  if(found == 1) {
    busstart* lastBusstart = node->edge;
    while(lastBusstart->next != NULL) {
      lastBusstart = lastBusstart->next;
    }
    addTime(lastBusstart, hour, min);
  }
  //if not found: lagg till en busstart 
  //och starttime
  if(found == 0) {
    busstart* newBusstart = malloc(sizeof(busstart));
    addTime(newBusstart, hour, min);
    // printf("line: %d, node: %p newbusstart: %p\n",
    //            line, node, newBusstart);
    newBusstart->line = line;  
    if(node->edge == NULL) {
      node->edge = newBusstart;
    } else {   
      busstart* lastBusstart = node->edge;
      while(lastBusstart->next != NULL) {
        lastBusstart = lastBusstart->next;
      }
      lastBusstart->next = newBusstart;
    } 
  }
}

/**
   Prints list of nodes and their names with their connections
   (Function is for debugging)
   @param viewConnections 0 or 1 depending on if you want to show each node's connections or not
   @param list list of nodes to print
 */
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
        
        printf("%d, >%s line: %d\n", i, ((node*)(tempEdge->node))->name, tempEdge->line);
        tempEdge = tempEdge->next;
        i++;
        
      }

    } else if (viewConnections == 2) {
      busstart* tempEdge = tempNode->edge;
      while(tempEdge != NULL) {
        printf("%d >", tempEdge->line);
        edgetime* tempTime = tempEdge->times;
        while(tempTime != NULL) {
          printf("%d:%d, ", tempTime->hours, tempTime->minutes);
          tempTime = tempTime->next;
        }
        tempEdge = tempEdge->next;
        puts(" ");
      } 
    }
    tempNode = tempNode->next;
  }
}



/**
   Gets minutes of travel between two stations
   @param visitedList list of previously searched nodes
   @param from name of start bus stop
   @param to name of destination bus stop
   @param bus bus number we are travelling on
   @param time accumulated travel time
   @return minutes it takes between from and to on the bus number
 */
int getTravelTime(node* visitedList, node* from, node* to, int bus, int time) {
  node* visited = visitedList;
  int finalCount = 0;
  int timeCount = time;
  newNode(&visited, from->name);
  edgedata* tempEdge = from->edge;
  while(tempEdge != NULL) {
    if(tempEdge->line == bus) {
      node* tempNode = ((node*) tempEdge->node);
      if(findNode(visited, tempNode->name) == NULL) {
          newNode(&visited, tempNode->name);
          timeCount += tempEdge->time;
          // printf("vi soker i: %s\n", tempNode->name);
          if(tempNode == to) {
            finalCount = timeCount;

            //frigör minnet av visitedlist. detta ballar ocksa ur
            //får invalid ptr error
            //node* tempNode = visited;
            //while(tempNode != NULL) {
            //node* killThisNode = tempNode;
            //tempNode = tempNode->next;
            //free(killThisNode);
            //}

            return timeCount;
          } else {
            getTravelTime(visited, tempNode, to, bus, timeCount);
          }
        }
    }
    tempEdge = tempEdge->next;
  }
  return 0;
}
