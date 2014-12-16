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

typedef struct edgetime {
  int hours;
  int minutes;
  void* next;
} edgetime;

typedef struct busstart {
  int line;
  edgetime* times;
  void* next
} busstart;

typedef struct node {
  char* name;
  void* edge;
  void* next;
} node;

node* root;
node* timetable = NULL;

FILE* fp;
char timetableFileName[] = "start.txt";
char inputFileName[] = "natverk.txt";
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
      if(finalName[length] != '/' && 
         finalName[length] != '-') {
        finalName[length] = '\0';
      }
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
    //
  }
  //if not found: lagg till en busstart 
  //och starttime
  if(found == 0) {
    //   puts("en ny busstart har");
    busstart* newBusstart = malloc(sizeof(busstart));
    addTime(newBusstart, hour, min);
    // printf("line: %d, node: %p newbusstart: %p\n",
    //            line, node, newBusstart);
    newBusstart->line = line;  
    if(node->edge == NULL) {
    
      node->edge = newBusstart;
      
      //addTime(newBusstart, hour, min);
    } else {
    
      busstart* lastBusstart = node->edge;
      while(lastBusstart->next != NULL) {
        lastBusstart = lastBusstart->next;
      }
      lastBusstart->next = newBusstart;
      // addTime(newBusstart, hour, min);
    
    } 
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

void possiblePaths(char* from, char* to, char* arrTime, char* destTime) {
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
      searchPath(visitedList, secondNode, toNode, tempEdge->line, arrTime, destTime);
      
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

int getTravelTime(node* visitedList, node* from, node* to, int bus, int time) {
  node* visited = visitedList;
  if(visited == NULL) {
    visited = NULL;
  }
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
            return timeCount;
          } else {
            return getTravelTime(visited, tempNode, to, bus, timeCount);
          }
        }
    }
    tempEdge = tempEdge->next;
  }
}
/**
 * does what it says it does
 * 
 *
 */
int timeToMinutes(int hours, int minutes) {
  int newMins = (60*hours) + minutes;
  return newMins;
}

int minsToHours(int minutes) {
  int newHours = (int) (minutes - (minutes % 60))/60;
  return newHours;
}

void printMinsToClock(int finalMins) {
  char tempHours[3];
  if(minsToHours(finalMins) < 10) {
    sprintf(tempHours, "%c%d", '0', minsToHours(finalMins));
  } else {
    sprintf(tempHours, "%d", minsToHours(finalMins));
  }
  char tempMins[3];
  if((finalMins % 60) < 10) {
    sprintf(tempMins, "%c%d", '0', (finalMins % 60));
  } else {
    sprintf(tempMins, "%d", (finalMins % 60));
  }
  tempHours[2] = '\0';
  tempMins[2] = '\0';
  printf("%s:%s", tempHours, tempMins);
}

void getTimes(node* path, int bus, int travelTime, int hour, int minute, char* action) {
  node* firstNode = path;
  node* lastNode = getLastNode(path);
  node* startNode1 = NULL;
  node* startNode2 = NULL;
  node* finalNode = NULL;
  node* tempNode = timetable;
  while(tempNode != NULL) {
    busstart* tempEdge = tempNode->edge;
    while(tempEdge != NULL) {
      if(tempEdge->line == bus) {
        if(startNode1 == NULL) {
          startNode1 = tempNode;
        } else {
          startNode2 = tempNode;
        }
      }
      tempEdge = tempEdge->next;
    }
    tempNode = tempNode->next;
  }

  //Vilken av dessa aker vi da fran?
  if(!strcmp(firstNode->name, startNode1->name)) {
    finalNode = startNode1;
  } else if(!strcmp(firstNode->name, startNode2->name)) {
    finalNode = startNode2;
  } else if(!strcmp(lastNode->name, startNode2->name)) {
    finalNode = startNode1;
  } else if(!strcmp(lastNode->name, startNode1->name)) {
    finalNode = startNode2;
  }

  if(finalNode == NULL) {
    //Kolla vilken som ar kortast sa vet jag vilken av hallplatserna vi startar fran
    int from1toStart = getTravelTime(NULL, findNode(root, startNode1->name), findNode(root, firstNode->name), bus, 0);
    int from1toEnd = getTravelTime(NULL, findNode(root, startNode1->name), findNode(root, lastNode->name), bus, 0);
    //printf("From1Tostart: %d, from1toend: %d\n", from1toStart, from2toStart);
    if(from1toStart < from1toEnd) {
      finalNode = startNode1;
    } else {
      finalNode = startNode2;
    }
  }
  int timeToStart = getTravelTime(NULL, findNode(root, finalNode->name), findNode(root, firstNode->name), bus, 0);
  //printf("mellan %s och %s ar det %d\n", findNode(root, finalNode->name)->name, findNode(root, firstNode->name)->name, timeToStart);
  //tid vi tidigast kan aka:
  //leaveHour:leaveMinute + timeToStart
  int newTime = timeToMinutes(hour, minute+timeToStart);
  
  busstart* tempBusstart = ((busstart*) findNode(timetable, finalNode->name)->edge);
  while(tempBusstart->line != bus) {
    tempBusstart = tempBusstart->next;
  }
  
  //I want to leave before XX:XX
  ///* TODO:  */KONTROLLERA TIDERNA
  int finalMins = 0;
  if(!strcmp(action, "leave")) {
    edgetime* tempEdgetime = tempBusstart->times;
    //Jag vill aka tidigast
    while(tempEdgetime != NULL) {
      finalMins = timeToMinutes(tempEdgetime->hours, tempEdgetime->minutes);
      if(finalMins > newTime) {
        break;
      }
      tempEdgetime = tempEdgetime->next;
    }
    
    printf("Bus leaves from %s at ", firstNode->name);
    printMinsToClock(finalMins-timeToStart);  
    printf("\n");
    printf("You will arrive at %s at ", lastNode->name);
    printMinsToClock(finalMins+travelTime-timeToStart);
    printf("\n");

  } else if (!strcmp(action, "arrive")) {
    //I WANT TO ARRIVE BEFORE XX:XX
    ///* TODO:  */KONTROLLERA TID , + time to last kanske)
    edgetime* tempEdgetime = tempBusstart->times;
    //Jag vill komma fram senast e klar
    while(tempEdgetime != NULL) {
      if(tempEdgetime->next != NULL) {
        edgetime* nxt = tempEdgetime->next;
        finalMins = timeToMinutes(tempEdgetime->hours, tempEdgetime->minutes);
        int possible = (timeToMinutes(nxt->hours, nxt->minutes) + travelTime + timeToStart);
        
        if((timeToMinutes(nxt->hours, nxt->minutes) + travelTime + timeToStart) > timeToMinutes(hour, minute)) {
          break;
        }
      }
      tempEdgetime = tempEdgetime->next;
    }
    //Printa tiden for din hallplats 
    printf("Bus leaves from %s at ", firstNode->name);
    printMinsToClock(finalMins-timeToStart); //+timeToStart  
    printf("\n");
    printf("You will arrive at %s at ", lastNode->name);
    printMinsToClock(finalMins+travelTime-timeToStart); //+timeToStart
    printf("\n");
  }
}

void printTravelPath(node* list, int busline, char* travelTime, char* action) {
  printf("\n -- Possible path by bus %d:\n", busline);
  node* tempNode = list;
  int totaltime = 0;
  node* lastNode;
  while(tempNode != NULL) {
    int time = 0;
    //get time from here to next
    node* rootNode = findNode(root, tempNode->name);
    edgedata* tempEdge = rootNode->edge;
    if(tempNode->next != NULL) {
      while(tempEdge != NULL) {

        node* nextRootNode = findNode(root, ((node*)(tempNode->next))->name);
        if(tempEdge->node == nextRootNode) {
          time = tempEdge->time;
        }

        if(nextRootNode != NULL) {
          lastNode = nextRootNode;
        }
        tempEdge = tempEdge->next;
      }

      printf("%s \t %d mins\n", tempNode->name, time);
      totaltime += time;
    } else {
      printf("%s\n", tempNode->name);
    }

      tempNode = tempNode->next;
  }
  puts("--------------------");
  printf("Total time: %d mins\n", totaltime);
  
  int hours = 0;
  int minutes = 0;
  
  if(strlen(travelTime) >= 5) {
    char* timeString = malloc(sizeof(char)*5);

    timeString = travelTime; 

    assert(strlen(timeString) == 5);
    char tempHour[3];
    memcpy(tempHour, &timeString[0], 2);
    tempHour[2] = '\0';  
    char tempMins[3];
    memcpy(tempMins, &timeString[3], 2);
    tempMins[2] = '\0';
    hours = atoi(tempHour);
    minutes = atoi(tempMins); 
    // printf("want to leave at, %d:%d\n", hours, minutes);
  }
  
  if(!strcmp(action, "arrive") || !strcmp(action, "arrive")) {
    getTimes(list, busline, totaltime, hours, minutes, action);
  }
  
}

void searchPath(node* visitedList, node* current, node* to, int busline, char* travelTime, char* action) {
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
          printTravelPath(visitedList, busline, travelTime, action);
          //printNodeList(0, visitedList);
        } else {
          strcpy(tempName, edgeNode->name);
          node* searchThisNode = newNode(&visitedList, tempName);

          searchPath(visitedList, searchThisNode, to, tempEdge->line, travelTime, action);
        }
      }
    }
    
    tempEdge = tempEdge->next;
   }
  //printNodeList(0, visitedList);
  free(tempName);
  //free(visitedList);
}

void initTimeTable() {
  fp = fopen(timetableFileName, "r");
  int step = 1;
  int lastCharWasComma = 0;
  
  char* step1 = malloc(sizeof(char)*5); //linje
  char* tempName = malloc(sizeof(char)*50);//name of bus stop
  char* step3 = malloc(sizeof(char)*5); //tid*/
 
  while(!feof(fp)) {
    c = fgetc(fp);
    if(c != ',' && !lastCharWasComma && c != '\n') {
      char buf[2];
      sprintf(buf, "%c", c);
      switch(step) 
        {
        case(1): strcat(step1, buf); break;
        case(2): strcat(tempName, buf); break;
        case(3): strcat(step3, buf); break;
        }
      lastCharWasComma = 0;
    }
    if(c == ',') {
      step++;
       lastCharWasComma = 1;
    } else {
      lastCharWasComma = 0;
    }

    if(c == '\n') {
      node* activeNode;

      int hours = 0;
      int minutes = 0;
      int len = strlen(step3);
      if(len == 4) {
        while(len > 0) {
          step3[len] = step3[len-1];
          len--;
        }
        step3[0] = '0';
      }
      assert(strlen(step3) == 5);
      char tempHour[3];
      memcpy(tempHour, &step3[0], 2);
      tempHour[2] = '\0';  
      char tempMins[3];
      memcpy(tempMins, &step3[3], 2);
      tempMins[2] = '\0';
      hours = atoi(tempHour);
      minutes = atoi(tempMins);

      //try add node
      if(findNode(timetable, tempName) == NULL) {
        activeNode = newNode(&timetable, tempName);

        //printf("addar nod: %s %s\n", tempName, step3);
      } else {
        activeNode = findNode(timetable, tempName);
      }

      //try add busnumber
      //add time;

      addStartTime(activeNode, atoi(step1), hours, minutes);

      step = 1;
      step1[0] = '\0';
      tempName[0] = '\0';
      step3[0] = '\0';

    }
  
  }
  
}

int main(int argc, char *argv[])
{

  if(argc == 3) {
    initBusStops();
    possiblePaths(argv[1], argv[2], "none", "none");
  } else if(argc == 5) {
    assert(!strcmp(argv[3], "leave") || !strcmp(argv[3], "arrive"));
    initBusStops();
    initTimeTable();
    possiblePaths(argv[1], argv[2], argv[4], argv[3]);    
  } else {
    puts("Invalid arguments. See readme for instructions");
  }

  //  possiblePaths("Centralstationen", "Cellovagen", "16:00", "leave");
 
  return 0;
}
