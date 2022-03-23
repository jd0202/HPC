#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif

int monte_carlo(double l, long long iterations)
{
    double x, theta, n;
    long long n_crossed = 0;
    long long i=0;
    for (i = 0; i < iterations; i++)
    {
        x = (double)rand() / (double)(RAND_MAX / l);
        theta = (double)rand() / (double)(RAND_MAX / M_PI);

        n = sin(theta) / 2.0;
        if (x + n >= l || x - n <= 0)
            n_crossed++;
    }
    return n_crossed;
}

int main(int argc, char *argv[])
{
    double l = 0.1;
    long long iterations = atoll(argv[1]);
    //printf("ingrese el valor de n\n");
    //	scanf("%d", &iterations);
    double p, pi;
    long long n_crossed;
    srand(time(NULL));
    clock_t start = clock();
    n_crossed = monte_carlo(l, iterations);
    p = n_crossed / (double)iterations;
    pi = 2.0 / (p * l);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\nPi: %f\nTiempo %.6f\n", p, pi, seconds);
    
    
    return 0;
}
