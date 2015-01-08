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

#endif
