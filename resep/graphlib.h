#include <stdlib.h>


#ifndef _GRAPHLIB_H_
#define _GRAPHLIB_H_

typedef struct edgedata {
  void* node;
  int line;
  int time;
  void* next;
} edgedata;

typedef struct edgetime {
  int hours;
  int minutes;
  void* next;
} edgetime;

typedef struct busstart {
  int line;
  edgetime* times;
  void* next;
} busstart;

typedef struct node {
  char* name;
  void* edge;
  void* next;
} node;

/**
  Gets the last node of a node list
  @param start of linked node list
  @return last node of list
 */
node* getLastNode(node* start);

/**
   Gets the last edgedata of an edge list
   @param start start of a linked list
   @return last edgedata of list
 */
edgedata* getLastEdge(edgedata* start);

/**
   Creates a new node with a given name
   Adds node at end of linked list
   @param list list to add a node
   @param name name of the node
   @return address to the new node
*/
node* newNode(node** list, char* name);

/**
   Finds a node in a node list
   @param list search this list of nodes
   @param name find node with this name
   @return address of found node if found, else NULL
 */
node* findNode(node* list, char* name);

/**
   Tries to remove a node from a node list
   @param list list of nodes
   @param name remove node with this name
 */
void removeNode(node* list, char* name);

/**
   Tries to remove an edgedata from a node
   @param node1 node to search for edges
   @param name remove edgedata with this name
*/
void removeEdge(node* node1, char* name);

/**
   Add a time when a bus leaves
   @param busline busline to add time to
   @param hour hour when bus leaves
   @param min minute when the bus leaves
 */
void addTime(busstart* busline, int hour, int min);

/**
   Add a time when a bus leaves the starting station
   @param node station to add time to
   @param busline busline to add time to
   @param hour hour when bus leaves
   @param min minute when the bus leaves
 */
void addStartTime(node* node, int line, int hour, int min);

/**
   Prints list of nodes and their names with their connections
   (Function is for debugging)
   @param viewConnections 0 or 1 depending on if you want to show each node's connections or not
   @param list list of nodes to print
 */
void printNodeList(int viewConnections, node* list);

/**
   Gets minutes of travel between two stations
   @param visitedList list of previously searched nodes
   @param from name of start bus stop
   @param to name of destination bus stop
   @param bus bus number we are travelling on
   @param time accumulated travel time
   @return minutes it takes between from and to on the bus number
 */
int getTravelTime(node* visitedList, node* from, node* to, int bus, int time);

#endif
