#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct neighbor {
  char* name;
  int line;
  int time;
  void* next;
};

struct node {
  char* name;
  void* firstNeighbor;
  void* next;
};


for(struct node* i = nodeVisited; i != NULL; i = nodeVisited->next){

}

FILE* fp;
char inputFileName[] = "natverk.txt";
char c;

struct node *root;
struct node *conductor;

char* shortestPath(char *h1, char *h2, int traveltime, int buschanges, int line)
{
  struct node *tempNode = root;
  int h1exists = 0;
  while(tempNode->next != NULL)
    {
      if (!strcmp(h1, tempNode->name))
        {
          h1exists = 1;
          break;
        }
      tempNode = tempNode->next;
    }
  
  if(h1exists)
    {
      struct neighbor *tempNeighbor = tempNode->firstNeighbor;
      while(tempNeighbor->next != NULL)
        {
          //Problem: oändlig loop när h1 och h2 är grannar till varandra
          int time = traveltime + tempNeighbor->time;
          int tempLine = tempNeighbor->line;
          int changes;
          //Öka buschanges med 1 för varje gång linjen byts
    
          if (tempLine != line)
            {
              changes = buschanges + 1;
            }
          else
            {
              changes = buschanges;
            }

          //kolla alla grannar var de går, osv i en loop
          if(!strcmp(h2, tempNeighbor->name))
            {
              // Samla ihop all data om eventuella byten och sedan jämför snabbaste
              printf("Hittade %s här: %s - Resetid: %d minuter - Antal byten: %d\n", h2, tempNode->name, time, changes - 1); 
            }
          else
            {
              shortestPath(tempNeighbor->name, h2, time, changes, tempLine);
            }
            
            

          tempNeighbor = tempNeighbor->next;
        }
      return "End of search";
    }
  else
    {
      return "Start station not found";
    };
}

void connectNodes(int line, struct node *node1, struct node *node2, int time)
{
  struct neighbor *tempNeighbor = node1->firstNeighbor;

  while(tempNeighbor->next != NULL)
    {
      tempNeighbor = tempNeighbor->next;
    }

  tempNeighbor->name = node2->name;

  tempNeighbor->line = line;
  tempNeighbor->time = time;

  if(tempNeighbor->next == NULL) {
    tempNeighbor->next = malloc(sizeof(struct neighbor));
  }

  /*  tempNeighbor = node2->firstNeighbor;

  while(tempNeighbor->name != NULL)
    {
      tempNeighbor = tempNeighbor->next;
    }

  tempNeighbor->name = node1->name;
  tempNeighbor->line = line;
  tempNeighbor->time = time;
  
  if(tempNeighbor->next == NULL) {
    tempNeighbor->next = malloc(sizeof(struct neighbor));
  }*/
}

int uniqueNames()
{
  fp = fopen(inputFileName, "r");
  int step = 1;

  char *step1 = malloc(sizeof(char)*5); //linje
  struct node *step2 = malloc(sizeof(struct node)); //h1
  struct node *step3 = malloc(sizeof(struct node)); //h2
  char *step4 = malloc(sizeof(char)*5); //tid

  int lastCharWasComma = 0;
  char *tempName = calloc(sizeof(char)*50, '\0');//max name of bus stop
  while(!feof(fp))
    {
      c = fgetc(fp);

      if (c != ',' && !lastCharWasComma)
        {
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
      
      if (c == ',')
        {
          if (step == 2 || step == 3)
            {
              int exists = 0;
              struct node *tempNode = root;

              while(tempNode->next != NULL)
                {
                  if (!strcmp(tempName, tempNode->name)) //Check if already exists
                    {
                      exists = 1;
                      switch(step)
                        {
                        case(2): step2 = tempNode; break;
                        case(3): step3 = tempNode; break;
                        }

                    }
                  tempNode = tempNode->next;
                }
              
              if(!exists)
                {
                  //Add node
                  conductor->name = strdup(tempName);
                  conductor->firstNeighbor = malloc(sizeof(struct neighbor));

                  switch(step)
                    {
                    case(2): step2 = conductor; break;
                    case(3): step3 = conductor; break;
                    }

                  /*Create a new node at end of list*/
                  conductor->next = malloc(sizeof(struct node));
                  conductor = conductor->next;
                }
              
              

              exists = 0;
              tempName[0] = '\0';
            }
          
          lastCharWasComma = 1;
          step++;
        }
      else
        {
          lastCharWasComma = 0;
        }
      
      if (c == '\n')
        {
          connectNodes(atoi(step1), step2, step3, atoi(step4));
          step1[0] = '\0';
          step4[0] = '\0';
          step = 1;
        }
    }

  fclose(fp);
  return 0;
}

int main()
{
  root = malloc(sizeof(struct node));
  conductor = root;
  //Initialize all unique bus stops to a linked list  
  uniqueNames();

  struct node *tempNode = root;
  while(tempNode->next != NULL)
    {
      printf("Hållplats: %s Grannar: ", tempNode->name);
      //print grannar
      struct neighbor *tempNeighbor = tempNode->firstNeighbor;
      while(tempNeighbor->next != NULL)
        {
          printf("%s, (%d, %d) ", tempNeighbor->name, tempNeighbor->line, tempNeighbor->time);
          tempNeighbor = tempNeighbor->next;
        }
      printf("\n");
      tempNode = tempNode->next;
    }
    
  puts("Buss mellan Vaksala torg och Prastgardsgatan:");
  puts(shortestPath("Graalsvagen", "Robo", 0, 0, 0));
  return 0;
}
