#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<math.h>

#define N 1000000

int main() {

    int i;
    double* A = malloc((N + 2) * sizeof(double));
    double* B = malloc((N + 2) * sizeof(double));
    double* A_temp = malloc((N + 2) * sizeof(double));
    double suma;

    //------------------------------------------------------------------
    // Wersja sekwencyjna

    for(i = 0; i < N + 2; i++) A[i] = (double)i/N;
    for(i =0; i < N + 2; i++) B[i] = 1.0 - (double)i/N;

    double t1 = omp_get_wtime();
    for(i = 0; i < N; i++){
        A[i] += A[i + 2] + sin(B[i]);
    }

    t1 = omp_get_wtime() - t1;

    suma = 0.0;
    for(i = 0; i < N + 2 ; i++) suma+=A[i];
    printf("Suma %lf, czas obliczen %lf\n", suma, t1);

    for(i = 0; i < N + 2; i++) A[i] = (double)i/N;
    for(i = 0; i < N + 2; i++) B[i] = 1.0 - (double)i/N;

    t1 = omp_get_wtime();

    //------------------------------------------------------------------
    // Wersja równoległa

    #pragma omp parallel num_threads(2) shared(A, B, A_temp)
    {
        #pragma omp for
        for(i = 0; i < N; i++) {
            A_temp[i] = A[i] + A[i+2] + sin(B[i]);
        }

        #pragma omp for
        for(i = 0; i < N; i++) {
            A[i] = A_temp[i];
        }
    }

    t1 = omp_get_wtime() - t1;

    suma = 0.0;
    for(i = 0; i < N + 2; i++) suma += A[i];
    printf("Suma %lf, czas obliczen rownoleglych %lf\n", suma, t1);

    free(A);
    free(B);
    free(A_temp);

    return 0;
}