#include <stdlib.h>
#include <stdio.h>
#include "graphlib.h"

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
