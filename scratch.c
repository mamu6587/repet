#include <stdlib.h>



 typedef struct{
 
   void* nasta;
   char* hallplats;
   int grannar;
} namnlista;
/*
namnlista första = malloc(sizeof(namnlista)+sizeof("""char[]""");

                          
                          //lägg in namnet i hållplats i första
                          //kolla nästa inlästa hållplats mot namnet
                          //om ny, mallokera och lägg in nästa i listan
                          //håll koll på hur många gånger namnet förekommer och
                          //skriv ned, detta är hur många grannar den har.
                          


                          första.nästa = (namlista) malloc(sizeof(namnlista)+sizeof("""char[]"""));

                      
                         
                          char hållplatsnamn[] = 



*/
int main() {
  
  namnlista* blu = malloc(sizeof(namnlista)+(sizeof(char)*10));
  blu->hallplats = "norra häl";

  namnlista* andra = malloc(sizeof(namnlista)+(sizeof(char)*10));
  blu->nasta = andra;
  
  andra->hallplats = "pollaks";
  
  
  printf("%s, %p\n", blu->hallplats,blu->nasta);
  printf("%s, %p\n", andra->hallplats,andra->nasta);
  return 0;
  
}

