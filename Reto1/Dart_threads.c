#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

long long iterations;
long long circle = 0;
int num_of_threads=8;


void *monte_carlo(void *id_arg)
{
    double x, y, d;
    long long circle = 0;
    long id = (long)id_arg;
    int size_per_thr = iterations / num_of_threads;
    int start_index = id * size_per_thr;
    int final_index = (id + 1) * size_per_thr;
	long long i=0;
    for (i = start_index; i < final_index; i++)
    {
        x = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        y = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        d = sqrt((x * x) + (y * y));
        if (d <= 1)
            circle++;
    }
}

int main(int argc, char **argv)
{
    printf("ingrese el valor de n\n");
    scanf("%d", &iterations);
    long rank;
    double pi;
    pthread_t tid[num_of_threads];
    srand(time(NULL));
    clock_t start = clock();
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_create(&tid[rank], NULL, monte_carlo, (void *)rank);
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_join(tid[rank], NULL);
    pi = 4.0 * circle / (double)iterations;
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Pi: %f\nLa ejecucion ha tomado %.4f segundos\n", pi, seconds);
    return 0;
}
