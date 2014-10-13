#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/*
int main(int argc, char** argv){
  for(int i = 0;i<argc;i++){
    printf("%s: %d\n",argv[i],strlen(argv[i]));
  }
  return 0;
}
*/

 typedef int *T;
 struct S {
   void *x;
 int y[26];
 };

// Variabeldeklarationer i en main-metod:


int main(){
  int* ptr;
 T foo;
 struct S bar;
 T *baz;
 struct S quux[7];
 struct S *frob;
 char *p;

 printf("%d\n",(sizeof(struct S)));
  printf("%p\n",bar);
  printf("%p\n",baz);
  printf("%p\n",quux);
  printf("%p\n",frob);
}
