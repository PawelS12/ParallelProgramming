#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SCALAR double
//#define SCALAR float

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max_liczba_wyrazow = 0;
    if (rank == 0) {
        printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
    }

    // Rozesłanie maksymalnej liczby wyrazów do wszystkich procesów
    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

    SCALAR local_sum_plus = 0.0;
    SCALAR local_sum_minus = 0.0;

    // Dekompocja 
    for (int i = rank; i < max_liczba_wyrazow; i += size) {
        int j = 1 + 4 * i;
        local_sum_plus += 1.0 / j;              // dla parzystych
        local_sum_minus += 1.0 / (j + 2.0);     // dla nieparzystych
    }

    SCALAR local_pi = 4 * (local_sum_plus - local_sum_minus);
    SCALAR global_pi = 0.0;

    // Redukcja wyników lokalnych do procesu o randze 0
    MPI_Reduce(&local_pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("PI obliczone: \t\t\t%20.15lf\n", global_pi);
        printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }

    MPI_Finalize();
    return 0;
}