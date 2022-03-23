#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>


long long iterations;
long long circle = 0;
int num_of_threads=2;


void *monte_carlo(void *id_arg)
{
    double x, y, d;
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
    //printf("ingrese el valor de n\n");
	//scanf("%lld", &iterations);
    iterations = atoll(argv[1]);
    long rank;
    double pi;
    pthread_t hilos[num_of_threads];
    srand(time(NULL));
    clock_t begin = clock();
    for (rank = 0; rank < num_of_threads; rank++)
    	pthread_create(&hilos[rank], NULL, monte_carlo, (void *)rank);
    for (rank = 0; rank < num_of_threads; rank++)
        pthread_join(hilos[rank], NULL);
    clock_t end = clock();
    pi = 4.0 * circle / (double)iterations;
    double time_spent = ((double)(end - begin) /  CLOCKS_PER_SEC);
    printf("Pi: %f\n", pi);
    printf("tiempo: %.6f\n", time_spent);
    pthread_exit(NULL);
    return 0;
}
