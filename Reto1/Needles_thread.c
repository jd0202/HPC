#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif
long long iterations;
int num_of_threads=8;
long long n_crossed = 0;
double l;

void *monte_carlo(void *id_arg)
{
    long id = (long)id_arg;
    int size_per_thr = iterations / num_of_threads;
    int start_index = id * size_per_thr;
    int final_index = (id + 1) * size_per_thr;
    double x, theta, n;
    long long i=0;
    for (i = start_index; i < final_index; i++)
    {
        x = (double)rand() / (double)(RAND_MAX / l);
        theta = (double)rand() / (double)(RAND_MAX / M_PI);
        n = sin(theta) / 2.0;
        if (x + n >= l || x - n <= 0)
            n_crossed++;
    }
}

int main(int argc, char **argv)
{
    int l = 1;
    //printf("ingrese el valor de n\n");
    //scanf("%d", &iterations);
    iterations = atoll(argv[1]);
    double p, pi;
    long rank;
    pthread_t tid[num_of_threads];
    srand(time(NULL));
    clock_t start = clock();
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_create(&tid[rank], NULL, monte_carlo, (void *)rank);
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_join(tid[rank], NULL);
    p = n_crossed / (double)iterations;
    pi = 2.0 / (p * l);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\nPi: %f\nTiempo %.6f\n", p, pi, seconds);
    return 0;
}
