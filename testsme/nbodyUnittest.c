#include "CUnit/Basic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//test-help functions
void setbodypos(body* c, short a, short b){
  c->x = a;
  c->y = b;
}

body* copybody(body g){
  body* newbody = calloc(1,sizeof(body));
  newbody->x = g.x;
  newbody->y = g.y; 
  newbody->vx = g.vx;
  newbody->vy = g.vy; 
  newbody->fx = g.fx; 
  newbody->fy = g.fy; 
  newbody->mass = g.mass;
  return newbody;
}

int init_suite1(void){
  return 0;
}

int clean_suite1(void){
  return 0;
}



//funktioner att testa:
//initierar 10 stj�rnor och s�tter deras v�rden till 1
//sedan k�r vi init p� samma star-array och kontrollerar
//att alla v�rden har �ndrats till till�tna v�rden

void testinit(){
  body* initbody = calloc(10,sizeof(body));

  for(int i = 0; i < 10; i++){
    initbody[i].vx = 1;
    initbody[i].vy = 1;
    initbody[i].fx = 1;
    initbody[i].fy = 1;
  }
  int wat = 10;
  init(&wat, initbody);
  for(int i = 0; i < 10; ++i){
    CU_ASSERT(initbody[i].x != 0 && initbody[i].y != 0);
    CU_ASSERT(initbody[i].x >= 200 && initbody[i].x <= 600 );
    CU_ASSERT(initbody[i].y >= 200 && initbody[i].y <= 600);
    CU_ASSERT(initbody[i].vx == 0);
    CU_ASSERT(initbody[i].vy == 0);
    CU_ASSERT(initbody[i].fx == 0);
    CU_ASSERT(initbody[i].fy == 0);
    CU_ASSERT(initbody[i].mass > 0);
  }
  
  free(initbody);
}


void testupdate(){
  //  void update(body* a, prec dt)
  // x & y ska inte f� vara f�r stora eller f�r sm� f�r att testa if;
  // kolla att den uppdaterar ordentligt, fr�gan �r hur: kolla att inte samma?
  // kolla f�r b�de positiva och negativa v�rden p� allt.
  int wat = 4;
  body* stars = calloc(wat,sizeof(body));
  //malloc(sizeof(body)* 8);


  prec gdt = 0.1;
  init(&wat,stars);
 
  for(int i = 0; i < wat; i++){
    setbodypos(&stars[i],400,400);  
  }
  //0 ska �ka rakt h�ger
  stars[0].fx = 5;
  stars[0].fy = 0;
  stars[0].vx = 10;
  stars[0].vy = 0;
  //1 ska �ka rakt v�nster
  stars[1].fx = -5;
  stars[1].fy = 0;
  stars[1].vx = -10;
  stars[1].vy = 0;
  //2 ska �ka rakt upp
  stars[2].fx = 0;
  stars[2].fy = 5;
  stars[2].vx = 0;
  stars[2].vy = 10;
  //3 ska �ka rakt ner
  stars[3].fx = 0;
  stars[3].fy = -5;
  stars[3].vx = 0;
  stars[3].vy = -10;

  for(int i = 0; i < 4; i++){
    update(&stars[i],gdt);
    CU_ASSERT((stars[i].fx == 0) && (stars[i].fy == 0));
  }

  CU_ASSERT(stars[0].x > 400 && stars[0].vx > 10);
  CU_ASSERT(stars[1].x < 400 && stars[1].vx < -10);
  CU_ASSERT(stars[2].y > 400 && stars[2].vy > 10);
  CU_ASSERT(stars[3].y < 400 && stars[3].vy < -10);

  free(stars);
}

/**
   Skapar tv� array av stars
   En av arrayerna inneh�ller en star med 100x st�rre massa �n de andra
   K�r addforce mellan de tv� stj�rnorna i varje array
   Kollar s� att det skapas kraft 
   Kollar s� att de dras mot varandra
   Kollar s� att stj�rnan med stor massa p�verkar kraften mer �n de andra
 */
void testaddForce(){
  //  void addForce(body* a, body* b)
  //skall testa den vanliga logiken och �ven distance-if-satsen

  body* stars = calloc(2,sizeof(body));
  body* stars2 = calloc(2,sizeof(body));
  //malloc(sizeof(body) * 4);

  //kolla f�rst att den s�tter kraften r�tt mellan tv� kroppar
  for(int i = 0; i < 2; i++){
    stars[i].mass = 1;
    stars2[i].mass = 1+ i*100;
  }

  setbodypos(&stars[0], 350, 450);
  setbodypos(&stars[1], 450, 350);
  
  setbodypos(&stars2[0], 350, 350);
  setbodypos(&stars2[1], 450, 450);
  
  addForce(&stars[0],&stars[1]);
  addForce(&stars2[0], &stars2[1]);

  CU_ASSERT((stars[0].fx > 0 )&&(stars[0].fy) < 0);
  CU_ASSERT((stars[1].fx < 0 )&&(stars[1].fy) > 0);
  CU_ASSERT(stars[0].fx < stars2[0].fx);
 
  free(stars);
  free(stars2);
}




/**
   Skapar en array av 3 stj�rnor
   K�r updateForces d�r vi uppdaterar alla stj�rnors kraft och position
   
 */
void testupdateForces(){
  //  updateForces(int N, body* star)
  // kolla att alla v�rden �ndras p� b�da i paret

  int num = 3;

  body* stars = calloc(num,sizeof(body));
  
  init(&num, stars);

  body* test1;
  body* test2;
  body* test3;

  

  for(int i = 0; i < 3; i++){
    setbodypos(&stars[i], 350+i*50, 350+i*50);
    stars[i].mass = 1;
  }
  
  test1 = copybody(stars[0]);
  test2 = copybody(stars[1]);
  test3 = copybody(stars[2]);

  int i = 0;
  while( i< 50 ){
    updateForces(3, stars);
    i++;
  }
  


  //stars0 flyttar sig
  CU_ASSERT(test1->x != stars[0].x);
  CU_ASSERT(test1->y != stars[0].y);
  CU_ASSERT(test1->vx != stars[0].vx);
  CU_ASSERT(test1->vy != stars[0].vy);

  //stars1 �r stilla
  CU_ASSERT(test2->x == stars[1].x);
  CU_ASSERT(test2->y == stars[1].y);

  //stars 2 flyttar sig
  CU_ASSERT(test3->x != stars[2].x);
  CU_ASSERT(test3->y != stars[2].y);
  CU_ASSERT(test3->vx != stars[2].vx);
  CU_ASSERT(test3->vy != stars[2].vy);

  //stars 0 och 2 har lika och motsatt hastighet
  CU_ASSERT(stars[0].vx == -(stars[2].vx));
  CU_ASSERT(stars[0].vy == -(stars[2].vy));

  free(stars);
  
  }


int main(){
  CU_pSuite pSuite = NULL;
  CU_initialize_registry();
  pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
  
  if (pSuite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(
     
     (NULL == CU_add_test(pSuite, "Test of update", testupdate)) 
      || (NULL == CU_add_test(pSuite, "Test of addForce", testaddForce)) 
      || (NULL == CU_add_test(pSuite, "Test of init", testinit)) 
     || (NULL == CU_add_test(pSuite, "Test of updateForces", testupdateForces)))
{
    CU_cleanup_registry();
    return CU_get_error();
  }

  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
