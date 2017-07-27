#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int aleatorio(int min, int max);
double obtenerTiempoActual();

int main(int argc, char** argv)
{
  return 0;
}

int aleatorio(int min, int max)
{

  return (rand() % (max-min+1) + min);

}

double obtenerTiempoActual()
{

  struct timespec tsp;
  clock_gettime( CLOCK_REALTIME, &tsp);

  double secs = (double)tsp.tv_sec;
  double nano = (double)tsp.tv_nsec / 1000000000.0;

  return secs + nano;

}
