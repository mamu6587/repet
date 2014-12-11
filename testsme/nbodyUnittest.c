#include "./../main-iter.c"
#include "CUnit/Basic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



//test-help functions
void setbody(body* c, short a, short b){
  c->x = a;
  c->y = b;
}

void copybody(body g, body* b){
  b->x = g.x;
  b->y = g.y; 
  b->vx = g.vx;
  b->vy = g.vy; 
  b->fx = g.fx; 
  b->fy = g.fy; 
  b->mass = g.mass;
}

int init_suite1(void){
  return 0;
}

int clean_suite1(void){




  return 0;
}



//funktioner att testa:


void testinit(){
  //  void init(int N, body* star)
  // kolla att alla värden ligger inom tillåtna ramar, och allt annat är 0
  body* initbody = calloc(10,sizeof(body));


  for(int i = 0;i < 11; i++){
    initbody[i].vx = 1;
    initbody[i].vy = 1;
    initbody[i].fx = 1;
    initbody[i].fy = 1;
  }
  init(10, initbody);
  for(int i = 0; i <= 10; ++i){
    CU_ASSERT(initbody[i].x <= 450 && initbody[i].x >= 350);
    CU_ASSERT(initbody[i].y <= 450 && initbody[i].y >= 350);
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
  // x & y ska inte få vara för stora eller för små för att testa if;
  // kolla att den uppdaterar ordentligt, frågan är hur: kolla att inte samma?
  // kolla för både positiva och negativa värden på allt.

  body* updatebody = calloc(4,sizeof(body));
  //malloc(sizeof(body)* 8);


  prec gdt = 0.01;
  init(4,updatebody);
  setbody(&updatebody[0],-401,0);  
  setbody(&updatebody[1],0,-401);
  setbody(&updatebody[2],0,0);
  setbody(&updatebody[3],0,0);
  updatebody[2].vx = -10;
  updatebody[2].fy = -10;
  updatebody[3].fx = 10;
  updatebody[3].vy = 10;
  CU_ASSERT(updatebody[0].x > -400 && updatebody[0].y != 0);
  CU_ASSERT(updatebody[1].y > -400 && updatebody[1].x != 0);
  CU_ASSERT((updatebody[2].x < 0) && (updatebody[2].y < 0));
  CU_ASSERT((updatebody[3].y > 0) && (updatebody[3].x > 0));
  for(int i = 0; i < 4; i++){
    CU_ASSERT((updatebody[i].fx == 0) && (updatebody[i].fy == 0));
  }    
  free(updatebody);
}

void testaddForce(){
  //  void addForce(body* a, body* b)
  //skall testa den vanliga logiken och även distance-if-satsen

  body* forceaddbody = calloc(2,sizeof(body));
  body* forceaddbody2 = calloc(2,sizeof(body));
  //malloc(sizeof(body) * 4);

  //kolla först att den sätter kraften rätt mellan två kroppar
  for(int i = 0; i < 3; i++){
    forceaddbody[i].mass = 1;
    forceaddbody2[i].mass = 100;
  }

  setbody(&forceaddbody[0], 350, 450);
  setbody(&forceaddbody[1], 450, 350);
  
  setbody(&forceaddbody2[0], 400, 400);
  setbody(&forceaddbody2[1], 400, 400);
  
  addForce(&forceaddbody[0],&forceaddbody[1]);
  addForce(&forceaddbody2[0], &forceaddbody2[1]);
  
  CU_ASSERT((forceaddbody[0].fx > 0 )&&(forceaddbody[0].fy) < 0);
  printf("fx = %d, fy = %d",forceaddbody[1].fx,forceaddbody[1].fy);
  CU_ASSERT((forceaddbody[1].fx < 0 )&&(forceaddbody[1].fy) > 0);

  //borde testa det här på något bättre sätt, men i nuläget kommer jag inte på jhur; xdist och ydist kommer antingen vara 0 eller > 0.0001, och i båda fallen går det inte att testa if-satsen
  CU_ASSERT((forceaddbody2[0].fx == 0)&&(forceaddbody2[0]).fy == 0);
  CU_ASSERT((forceaddbody2[1].fx == 0)&&(forceaddbody2[1]).fy == 0);
  

  free(forceaddbody);
  free(forceaddbody2);
}





void testupdateForces(){
  //  updateForces(int N, body* star)
  // kolla att alla värden ändras på båda i paret

  body* updateforcesbody = calloc(3,sizeof(body));
  body test1;
  body test2;
  body test3;
  
  init(3, updateforcesbody);
  for(int i = 0; i < 3; i++){
    setbody(&updateforcesbody[i],350+i*50,350+i*50);
}
  copybody(updateforcesbody[0],&test1);
  copybody(updateforcesbody[1],&test2);
  copybody(updateforcesbody[2],&test3);
  int i = 0;
  while( i< 20 ){
    updateForces(2, updateforcesbody);
    i++;
  }
  

  printf("test = %d, updateforcesbody = %d",test1.y,updateforcesbody[0].y);

  CU_ASSERT(test1.x != updateforcesbody[0].x);
  CU_ASSERT(test1.y != updateforcesbody[0].y);
  CU_ASSERT(test1.vx != updateforcesbody[0].vx);
  CU_ASSERT(test1.vy != updateforcesbody[0].vy);


  CU_ASSERT(test2.x != updateforcesbody[1].x);
  CU_ASSERT(test2.y != updateforcesbody[1].y);
  CU_ASSERT(test2.vx != updateforcesbody[1].vx);
  CU_ASSERT(test2.vy != updateforcesbody[1].vy);


  CU_ASSERT(test3.x != updateforcesbody[2].x);
  CU_ASSERT(test3.y != updateforcesbody[2].y);
  CU_ASSERT(test3.vx != updateforcesbody[2].vx);
  CU_ASSERT(test3.vy != updateforcesbody[2].vy);


  free(updateforcesbody);
  
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
     || (NULL == CU_add_test(pSuite, "Test of updateForces", testupdateForces))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
