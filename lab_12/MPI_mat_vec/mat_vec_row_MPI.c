#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define WYMIAR 200 
#define ROZMIAR (WYMIAR*WYMIAR)

void mat_vec(double* a, double* x, double* y, int n, int nt);

int main(int argc, char** argv) {
    static double x[WYMIAR], y[WYMIAR], z[WYMIAR];
    double *a;
    double t1;
    int n, nt, i;
    
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    n = WYMIAR;

    for (i = 0; i < WYMIAR; i++) x[i] = 0.0;

    if (rank == 0) {
        a = (double *)malloc(ROZMIAR * sizeof(double));
        for (i = 0; i < ROZMIAR; i++) a[i] = 1.0 * i;
        for (i = 0; i < WYMIAR; i++) x[i] = 1.0 * (WYMIAR - i);

        nt = 1;
        printf("Sequential execution\n");
        t1 = MPI_Wtime();
        mat_vec(a, x, y, n, nt); // a * x, wynik w y
        t1 = MPI_Wtime() - t1;

        printf("\tExecution time: %lf, Gflop/s: %lf, GB/s> %lf\n", t1, 2.0e-9 * ROZMIAR / t1, (1.0 + 1.0 / n) * 8.0e-9 * ROZMIAR / t1);
    }

    if (size > 1) {
        int n_wier = WYMIAR / size;
        double *a_local = (double *)malloc(WYMIAR * n_wier * sizeof(double));
        
        if (rank == 0) {
            MPI_Scatter(a, WYMIAR * n_wier, MPI_DOUBLE, a_local, WYMIAR * n_wier, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        } else {
            MPI_Scatter(NULL, WYMIAR * n_wier, MPI_DOUBLE, a_local, WYMIAR * n_wier, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }

        MPI_Bcast(x, WYMIAR, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        for (i = 0; i < n_wier; i++) {
            double t = 0.0;
            int ni = i * n;
            for (int j = 0; j < n; j++) {
                t += a_local[ni + j] * x[j];
            }
            z[i] = t;
        }

        if (rank == 0) {
            MPI_Gather(MPI_IN_PLACE, n_wier, MPI_DOUBLE, z, n_wier, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        } else {
            MPI_Gather(z, n_wier, MPI_DOUBLE, z, n_wier, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }

        if (rank == 0) {
            for (i = 0; i < WYMIAR; i++) {
                if (fabs(y[i] - z[i]) > 1.e-9 * z[i]) {
                    printf("Error! i=%d, y[i]=%lf, z[i]=%lf\n", i, y[i], z[i]);
                } else {
                    printf("Correct! i=%d, y[i]=%lf, z[i]=%lf\n", i, y[i], z[i]);
                }
            }
        }

        free(a_local);
        if (rank == 0) free(a);
    }

    MPI_Finalize();
    return 0;
}

void mat_vec(double* a, double* x, double* y, int nn, int nt) {
    register int n = nn;
    register int i;
    for (i = 0; i < n; i += 2) {
        register double ty1 = 0;
        register double ty2 = 0;
        register int j;

        for (j = 0; j < n; j += 2) {
            register double t0 = x[j];
            register double t1 = x[j + 1];
            register int k = i * n + j;
            ty1 += a[k] * t0 + a[k + 1] * t1;
            ty2 += a[k + n] * t0 + a[k + 1 + n] * t1;
        }

        y[i] = ty1;
        y[i + 1] += ty2;
    }
}