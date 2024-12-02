#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10
#define WARIANT 2

int main () {
    double a[WYMIAR][WYMIAR];

    for(int i = 0; i < WYMIAR; i++){
      for(int j = 0; j < WYMIAR; j++) {
        a[i][j] = 1.02 * i + 1.01 * j;
      }
    }

    double suma = 0.0;
    for(int i = 0; i < WYMIAR; i++) {
      for(int j = 0; j < WYMIAR; j++) {
        suma += a[i][j];
      }
    }
    
    printf("Suma wyrazow tablicy: %lf\n", suma);

    omp_set_nested(1);
    double suma_parallel = 0.0; 
    
    //-----------------------------------------------------------------------------
    // Wariant 1
    
    #if WARIANT == 1
    #pragma omp parallel for reduction(+:suma_parallel) schedule(static, 2) num_threads(4) ordered
    for(int i = 0; i < WYMIAR; i++) {
      for(int j = 0; j < WYMIAR; j++) {
        suma_parallel += a[i][j];
        #pragma omp ordered
        printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num()); 
      }
      printf("\n");
    }
    #endif
    
    //-----------------------------------------------------------------------------
    // Wariant 2
    
    #if WARIANT == 2
    for(int j = 0; j < WYMIAR; j++) {
      #pragma omp parallel for reduction(+:suma_parallel) schedule(dynamic) num_threads(4) ordered
      for(int i = 0; i < WYMIAR; i++) {
        suma_parallel += a[i][j];
      #pragma omp ordered
      printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num()); 
      }
      printf("\n");
    }
    #endif

    //-----------------------------------------------------------------------------
    // Wariant 3
    
    #if WARIANT == 3
    #pragma omp parallel num_threads(4)
    {
      double suma_thread = 0.0;  
      
      #pragma omp for schedule(static) nowait ordered
      for (int j = 0; j < WYMIAR; j++) {
          for (int i = 0; i < WYMIAR; i++) {
              suma_thread += a[i][j]; 
              #pragma omp ordered
              printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num()); 
          }
          #pragma omp ordered
          printf("\n");
      }
      
      #pragma omp critical
      {
          suma_parallel += suma_thread;  
      }
    }
    #endif
      
    //-----------------------------------------------------------------------------
    // Wariant 4
    
    #if WARIANT == 4
    #pragma omp parallel for schedule(static, 2) num_threads(3) ordered reduction(+:suma_parallel)
    for (int i = 0; i < WYMIAR; i++) {
        #pragma omp ordered
        {
            #pragma omp parallel for schedule(static, 2) num_threads(2) reduction(+:suma_parallel)
            for (int j = 0; j < WYMIAR; j++) {
                suma_parallel += a[i][j];
                printf("(%1d,%1d)-W_%1d/%1d ", i, j, omp_get_thread_num(), omp_get_num_threads());
            }
            printf("\n");
        }
    }
    #endif

  printf("Suma wyrazow tablicy rownolegle: %lf\n", suma_parallel);

  return 0;
}