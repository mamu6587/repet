#include <stdlib.h>



 typedef struct{
 
   void* nasta;
   char* hallplats;
   int grannar;
} namnlista;
/*
namnlista f�rsta = malloc(sizeof(namnlista)+sizeof("""char[]""");

                          
                          //l�gg in namnet i h�llplats i f�rsta
                          //kolla n�sta inl�sta h�llplats mot namnet
                          //om ny, mallokera och l�gg in n�sta i listan
                          //h�ll koll p� hur m�nga g�nger namnet f�rekommer och
                          //skriv ned, detta �r hur m�nga grannar den har.
                          


                          f�rsta.n�sta = (namlista) malloc(sizeof(namnlista)+sizeof("""char[]"""));

                      
                         
                          char h�llplatsnamn[] = 



*/
int main() {
  
  namnlista* blu = malloc(sizeof(namnlista)+(sizeof(char)*10));
  blu->hallplats = "norra h�l";

  namnlista* andra = malloc(sizeof(namnlista)+(sizeof(char)*10));
  blu->nasta = andra;
  
  andra->hallplats = "pollaks";
  
  
  printf("%s, %p\n", blu->hallplats,blu->nasta);
  printf("%s, %p\n", andra->hallplats,andra->nasta);
  return 0;
  
}

