#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

int f_threadprivate;
#pragma omp threadprivate(f_threadprivate)

int main() {
  
#ifdef _OPENMP
    printf("Kompilator rozpoznaje dyrektywy OpenMP\n\n");
#endif

    int liczba_watkow;
    int a_shared = 1;
    int b_private = 2;
    int c_firstprivate = 3;
    int e_atomic = 5;

    omp_set_num_threads(5);
    
    printf("Przed wejsciem do obszaru rownoleglego -  nr_threads %d, thread ID %d\n", omp_get_num_threads(), omp_get_thread_num());
    printf("\ta_shared \t= %d\n", a_shared);
    printf("\tb_private \t= %d\n", b_private);
    printf("\tc_firstprivate \t= %d\n", c_firstprivate);
    printf("\te_atomic \t= %d\n", e_atomic);
      
  
    #pragma omp parallel default(none) shared(a_shared, e_atomic) private(b_private) firstprivate(c_firstprivate )
    {
      int i;
      int d_local_private;
      
      #pragma omp barrier
      d_local_private = a_shared + c_firstprivate;

      for(i = 0; i < 10; i++){
          #pragma omp critical
          a_shared++; 
      }

      for(i = 0; i < 10; i++){
          c_firstprivate += omp_get_thread_num();
      }

      for(i = 0; i < 10; i++){
          #pragma omp atomic
          e_atomic += omp_get_thread_num();
      }

      f_threadprivate = omp_get_thread_num();

      #pragma omp critical
      { 
        printf("\nW obszarze rownoleglym: aktualna liczba watkow %d, moj ID %d\n", omp_get_num_threads(), omp_get_thread_num());
        printf("\ta_shared \t= %d\n", a_shared);
        printf("\tb_private \t= %d\n", b_private);
        printf("\tc_firstprivate \t= %d\n", c_firstprivate);
        printf("\td_local_private = %d\n", d_local_private);
        printf("\te_atomic \t= %d\n", e_atomic); 
        printf("\tf_threadprivate = %d\n\n", f_threadprivate);
      }
    }

    #pragma omp parallel
    {
      #pragma omp critical
      {
        printf("Drugi obszar rownolegly: liczba watkow %d, moj ID %d, f_threadprivate = %d\n", omp_get_num_threads(), omp_get_thread_num(), f_threadprivate);
      }
    }
    
    printf("\nPo zakonczeniu obszaru rownoleglego:\n");
    printf("\ta_shared \t= %d\n", a_shared);
    printf("\tb_private \t= %d\n", b_private);
    printf("\tc_firstprivate \t= %d\n", c_firstprivate);
    printf("\te_atomic \t= %d\n", e_atomic);
      
    return 0;
}