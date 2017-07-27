#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int aleatorio(int min, int max);
double obtenerTiempoActual();
void * sumarSubArreglo(void * rango);

struct rango{
  int * arreglo;
  int inicio;
  int fin;
} rango;


int main(int argc, char** argv){
  double tiempoInicial = obtenerTiempoActual();
  if (argc != 3){
    printf("Uso del programa <Tamano del arreglo> <Numero de hilos>\n");
    return -1;
  }
  else{
    int n = atoi(argv[1]);
    int nhilos = atoi(argv[2]);
    int newsize = n;

    int * arreglo = (int *)malloc(sizeof(int) * n);

    for (int i=0; i<n; i++){
      arreglo[i] = aleatorio(1, 10);
      printf("+%d", arreglo[i]);
    }
    
    while((newsize % nhilos)!=0)
    	newsize -= 1;

    int sizeSub = newsize / nhilos;

    pthread_t * idHilos = (pthread_t *)malloc(sizeof(pthread_t) * nhilos);
    
    int c = 0;
    long suma = 0;

    for (int x=0; x<nhilos; x++){
    	pthread_t h;
    	struct rango *r = (struct rango *)malloc(sizeof(struct rango));
    	r->arreglo = arreglo;
    	r->inicio = c;
    	r->fin = c + sizeSub - 1;
      if ((pthread_create(&h, NULL, sumarSubArreglo, (void *)r)<0)){
        printf("Algo salio mal con la creacion del hilo\n");
        return -1;
      }
      idHilos[x] = h;
      c += sizeSub;
    }

    if (newsize != n){
      printf("Numeros falntantes: %d\n",n-newsize);
      pthread_t h;
    	struct rango *r = (struct rango *)malloc(sizeof(struct rango));
    	r->arreglo = arreglo;
    	r->inicio = c;
    	r->fin = n - 1;
      if ((pthread_create(&h, NULL, sumarSubArreglo, (void *)r)<0)){
        printf("Algo salio mal con la creacion del hilo\n");
        return -1;
      }
      idHilos[nhilos-1] = h;
    }

    for (int x=0; x<nhilos; x++){
    	void * sumaparcial = malloc(sizeof(long));
      pthread_join(idHilos[x], sumaparcial);
      suma += *((long *)sumaparcial);
    }

    printf("\nLa suma de los elementos es: %lu\n",suma);
    
    double tiempoFinal = obtenerTiempoActual();

    printf("Tiempo de ejecucion: %f\n\n",(tiempoFinal-tiempoInicial));

    return 0;
  } 
  
}

void * sumarSubArreglo(void * rango1){
  struct rango *rangoooo = (struct rango *)rango1;
  long suma = 0;
  for (int i=rangoooo->inicio; i<=rangoooo->fin; i++)
    suma += rangoooo->arreglo[i];
  return (void *)suma;
}

int aleatorio(int min, int max){
  return (rand() % (max-min+1) + min);
}

double obtenerTiempoActual(){
  struct timespec tsp;
  clock_gettime(CLOCK_REALTIME, &tsp);

  double secs = (double)tsp.tv_sec;
  double nano = (double)tsp.tv_nsec / 1000000000.0;

  return secs + nano;
}
