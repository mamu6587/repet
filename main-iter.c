#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef ANIMATE
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define X_SIZE 800
#define Y_SIZE 800
#endif

#define prec float
#define PI 3.14159265359
#define gconst 6.673 // gravitationskonstanten, vad ska den vara?

static prec gdt = 0.01;

typedef struct {
  short x;
  short y;
  double fx;
  double fy;
  double vx;
  double vy;
  double mass;
  //x,y värden (position)
  //kraftvektor staffan was here
} body;


static prec newRand()
{
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}


static void resetForce(body* b) {
  b->fx = 0;
  b->fy = 0;
}

static void update(body* a, prec dt)
{

  if((a->x < -400 )||(a->y < -400)){  
    a->vx = newRand();//a->mass;
    a->vy = newRand();//a->mass;
    a->x = 400;
    a->y = 400;
    resetForce(a);
    return;
  }
  
  a->vx += a->fx*dt;//a->mass;
  a->vy += a->fy*dt;//a->mass;
  a->x += a->vx*dt + (a->fx*dt*dt)/2;
  a->y += a->vy*dt + (a->fy*dt*dt)/2;
    
  resetForce(a);
    // update_all_positions();  // update_all_positions();
  //clock_t start = clock();
  //clock_t step += 0.0001
  
  //start = nu
  //if nu = start+gdt, then update
}
//uppdaterar stjärnorna varje tick


static void addForce(body* a, body* b)
{
  double ydist = (a->y - b->y);
  double xdist = (a->x - b->x);
  double distance = sqrt((xdist*xdist)+(ydist*ydist));
 
  if (distance > 0.0001){

  
  double force = (a->mass * b->mass)/distance;
  a->fx -= force*xdist;
  a->fy -= force*ydist;
}
}




void init(int N, body* star)
{
  // skapa stjärnor
  // skapa array av bodies, malloc sizeof(body)
  for (int i = 0; i < N; i++)
   {
     star[i].x = 100 + (rand() % 200); // random number between 350-450; 
     star[i].y = 100 + (rand() % 200);
     star[i].vx = 0;//newRand(); // Vad ska vx slumpas till?
     star[i].vy = 0;//newRand();
     star[i].fx = 0;
     star[i].fy = 0;
     star[i].mass = newRand();
   }
}
// kör newRand N gånger, sparar/skapar resultatet i en array med stjärnor

static void updateForces(int N, body* star)
{

  // ett tidssteg
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
        {
          if (i != j )
            {
	      addForce(&star[i],&star[j]);
	      
              // star[i]->x += calculate force x(i, j)
              // star[j]->y += calculate force y(i,j)
            }
        }
    
    }

  for(int k = 0; k < N; k++){
    update(&star[k],gdt);
  }
  // update_all_positions  
  
}

// tar in en kraft N och arrayen med stjärnor. uppdaterar varje stjärnas kraft
  
  
  // Manually copy coordinates from stars into points (to be drawn).
  // Look at the manual file for XPoint to see which
  // format XPoint accepts its coordinates in.
#ifdef ANIMATE
static void copyToXBuffer(body* star, XPoint* points, int N)
{

  for(int i = 0; i < N; i++) {
    points[i].x = star[i].x;
    points[i].y = star[i].y;
    }
  // översätt koordinater till xpointkoordinater
}
#endif
 
 int main(int argc, char* argv[]) {
   
   int N = 200;
  int iter = 1000;

  if(argc == 3)
    {
      N = atoi(argv[1]);
      iter = atoi(argv[2]);
    }
  
  body* star = malloc(sizeof(body) * N); // skapa array av stjärnor
  init(N, star);
  printf("antal stars: %d\nstar[18]: %d, %d. \nstar[190]: %d, %d\n", N, 
	 star[18].x, star[18].y, star[190].x, star[190].y); 
  // två test-star för att se vad som finns

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
#endif

  free(points);
  free(star);
  return 0;
}
