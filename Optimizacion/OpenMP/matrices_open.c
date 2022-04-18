#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int size, num_threads, tid, i, j, k;
    size = atoi(argv[1]);
    double **A = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        A[i] = malloc(size * sizeof(double));

    double **B = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        B[i] = malloc(size * sizeof(double));

    double **C = malloc(size * sizeof(double *));
    for (i = 0; i < size; i++)
        C[i] = malloc(size * sizeof(double));

    clock_t start = clock();
    double spent_time = 0;
    srand(time(NULL));
#pragma omp parallel private(tid, i, j, k) shared(A, B, C, num_threads)
    {
        tid = omp_get_thread_num();
#pragma omp for
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                A[i][j] = rand() % 10;
#pragma omp for
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                B[i][j] = rand() % 10;
#pragma omp for
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                C[i][j] = 0;
#pragma omp for
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                for (k = 0; k < size; k++)
                    C[i][j] += A[i][k] * B[k][j];
    }
    clock_t end = clock();
    spent_time = (double)(end - start) / CLOCKS_PER_SEC;
    FILE *f = fopen("result.txt", "a");
    fprintf(f, "Tiempo de ejecucion: %.8f \n", spent_time);
    //printf("Tiempo de ejecucion: %.8f \n", spent_time);
    return 0;
}