#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define WARIANT 1

int main(int argc, char** argv) {
    int rank, size, prev, next;
    int value; // Zmienna przechowująca wartość przesyłaną w pierścieniu
    int tag = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    prev = (rank - 1 + size) % size; // Poprzednik
    next = (rank + 1) % size;        // Następca

    if (rank == 0) {
        value = 1; 
        printf("Proces %d wysyła liczbę %d do procesu %d\n", rank, value, next);
        MPI_Send(&value, 1, MPI_INT, next, tag, MPI_COMM_WORLD);

        MPI_Recv(&value, 1, MPI_INT, prev, tag, MPI_COMM_WORLD, &status);
        printf("Proces %d odebrał liczbę %d od procesu %d\n", rank, value, prev);
    } else {
        MPI_Recv(&value, 1, MPI_INT, prev, tag, MPI_COMM_WORLD, &status);
        printf("Proces %d odebrał liczbę %d od procesu %d\n", rank, value, prev);
        value++;

        if (rank != size - 1) {
            printf("Proces %d wysyła liczbę %d do procesu %d\n", rank, value, next);
            MPI_Send(&value, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        } else {

            #if WARIANT == 1
            printf("Proces %d wysyła liczbę %d do procesu %d\n", rank, value, next);
            MPI_Send(&value, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
            #endif

            #if WARIANT == 2
            printf("Proces %d kończy sztafetę z liczbą %d\n", rank, value);
            #endif
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return (0);
}