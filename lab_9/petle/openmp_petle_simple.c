#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18
#define WARIANT 2

int main () {
    double a[WYMIAR];

    #pragma omp parallel for default(none) shared(a)
    for(int i = 0; i < WYMIAR; i++) {
      a[i] = 1.02 * i;
    }
    
    double suma = 0.0;
    for(int i = 0; i < WYMIAR; i++) {
        suma += a[i];
    }
    
    printf("Suma wyrazow tablicy sekwencyjnie: %lf\n", suma);
    double suma_parallel = 0.0;
    
    #if WARIANT == 1
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) ordered
    for(int i = 0; i < WYMIAR; i++) {
      int id_w = omp_get_thread_num();
      suma_parallel += a[i];

      #pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
    }
    #endif

    #if WARIANT == 2
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) schedule(static, 3) num_threads(4) ordered
     for(int i = 0; i < WYMIAR; i++) {
      int id_w = omp_get_thread_num();
      suma_parallel += a[i];

      #pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
    }
    #endif

    #if WARIANT == 3
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) schedule(static) num_threads(4) ordered
    for(int i = 0; i < WYMIAR; i++) {
      int id_w = omp_get_thread_num();
      suma_parallel += a[i];

      #pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
    }
    #endif

    #if WARIANT == 4
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) schedule(dynamic, 2) num_threads(4) ordered
    for(int i = 0; i < WYMIAR; i++) {
      int id_w = omp_get_thread_num();
      suma_parallel += a[i];

      #pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
    }
    #endif

    #if WARIANT == 5
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel) schedule(dynamic) num_threads(4) ordered
    for(int i = 0; i < WYMIAR; i++) {
      int id_w = omp_get_thread_num();
      suma_parallel += a[i];

      #pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
    }
    #endif

    printf("\nSuma wyrazow tablicy rownolegle (z klauzula - reduction): %lf\n", suma_parallel);

    return 0;
}