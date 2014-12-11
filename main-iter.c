#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>


#ifdef ANIMATE
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X_SIZE 800
#define Y_SIZE 800
#endif

#define prec float

/**
 * \file
 * @author Staffan Edstrom, Magnus Muhr
 */

static prec gdt = 0.001;

typedef struct {
  short x;
  short y;
  double fx;
  double fy;
  double vx;
  double vy;
  double mass;
} body;

/**
 * Randomise a float number between 1 and 0
 * @return randomised number
 */
static prec newRand()
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  assert(r <= 1 && r > 0);
  return r;
}

/**
 * Set the force of a body to 0
 * @param b the affected body
 */
static void resetForce(body* b) {
  b->fx = 0;
  b->fy = 0;
}

/**
 * Update position and force of a body in a timespan
 * @param a the affected body
 * @param dt timespan
 */
static void update(body* a, prec dt)
{
  a->vx += a->fx*dt;
  a->vy += a->fy*dt;
  a->x += (int)(a->vx*dt + (a->fx*dt*dt)/2);
  a->y += (int)(a->vy*dt + (a->fy*dt*dt)/2);
    
  resetForce(a);
}

/**
 * Calculates the gravitational forces between two bodies and 
 * updates their forces accordingly
 * @param a the first body
 * @param b the second body
 */
static void addForce(body* a, body* b)
{

  double ydist = (a->y - b->y);
  double xdist = (a->x - b->x);
  double distance = 1.0f/sqrt((xdist*xdist)+(ydist*ydist));
    
  double force = (a->mass * b->mass)/distance;
  a->fx -= force*xdist;
  a->fy -= force*ydist;
  b->fx += force*xdist;
  b->fy += force*ydist;
}

/**
 * Initialise a number of bodies in an array of bodies
 * @param N number of bodies to be initalised
 * @param star array of bodies
 */
void init(int* N, body* star)
{
  // printf("int N i init: %d\n", *N);
  for (int i = 0; i < *N; i++)
   {
     star[i].x = 200 + (rand() % 400); 
     star[i].y = 200 + (rand() % 400);
     star[i].vx = 0;
     star[i].vy = 0;
     star[i].fx = 0;
     star[i].fy = 0;
     star[i].mass = newRand();
   }
}

/**
 * Updates forces and positions of bodies
 * @param N number of bodies to be updated
 * @param star array of bodies to be updated
 */
static void updateForces(int N, body* star)
{
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
        {
          if (i != j )
            {
	      addForce(&star[i],&star[j]);
            }
        }
    }

  for(int k = 0; k < N; k++){
    update(&star[k],gdt);
  }  
}


#ifdef ANIMATE
/**
 * Copy the coordinates of stars into points to be drawn
 * Formatted for being viewed in XPoint (see XPoint manual)
 * @param star array of bodies to be drawn
 * @param points XPoint coordinates
 * @param N number of bodies
 */
static void copyToXBuffer(body* star, XPoint* points, int N)
{
  for(int i = 0; i < N; i++) {
    points[i].x = star[i].x;
    points[i].y = star[i].y;
  }
}
#endif
 
/**
 * Start simulation of bodies in space
 * Prints time, number of bodies and number of iterations
 * @param argc number of arguments
 * @param argv[] array of arguments
 * @return 0 when finished
 */
#ifdef RUN
#ifndef TEST
int main(int argc, char* argv[]) {

  int N = 200;
  int iter = 1000;

  if(argc == 3)
    {
      //printf("%p börjar argv\n +1 = %p ska vara lika som: %p\n", argv, argv + 1, &argv[1]);
      N = atoi(*(argv + 1));
      iter = atoi(argv[2]);
    }

  assert(N > 0);
  assert(iter > 0);
  
  body* star = malloc(sizeof(body) * N); // skapa array av stjärnor
  // printf("pekare till stackvariabel N: %p\n", &N);
  init(&N, star);
  // testar att översätta mellan array-notation och pekararitmetik
  //printf("%p ska vara lika som: %p\n", star, &star[0]);
  //printf("%p ska vara lika som: %p\n", (star + 1), &star[1]);


#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint)*N);
  Display* disp;
  Window window, rootwin;
  int screen;

  disp = XOpenDisplay(NULL);
  screen = DefaultScreen(disp);
  rootwin = RootWindow(disp,screen);
  window = XCreateSimpleWindow(disp,rootwin,0,0,X_SIZE,Y_SIZE,1,0,0);
  GC gc = XCreateGC(disp, window, 0, 0);
  XSetForeground(disp, gc, WhitePixel(disp, screen));
  XSetBackground(disp, gc, BlackPixel(disp, screen));
  XMapWindow(disp,window);

  XClearWindow(disp,window);

  copyToXBuffer(star, points, N);
  XDrawPoints(disp, window, gc, points, N, 0);

  XFlush(disp);

#endif
  clock_t start = clock();
  for(int i = 0; i < iter; i++)
    {
      updateForces(N, star);
#ifdef ANIMATE
      copyToXBuffer(star, points, N);
      XDrawPoints(disp, window, gc, points, N, CoordModeOrigin);
      XClearWindow(disp,window);
#endif
    }
  clock_t stop = clock();
  float diff = (float)(stop - start)/CLOCKS_PER_SEC;
  printf("Total: %lf seconds\n",diff);
  printf("Bodies: %d\n",N);
  printf("Iterations: %d\n", iter);

#ifdef ANIMATE
  XCloseDisplay(disp);
  free(points);
  free(gc);
#endif

  free(star);
  return 0;
}
#endif
#endif

#ifdef TEST
#include "testsme/nbodyUnittest.c"
#endif
