#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long circle = 0;

long long monte_carlo(long long iterations)
{
    double x, y, d;
	long long i = 0;
    for (i = 0; i < iterations; i++)
    {
        x = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        y = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        d = sqrt((x * x) + (y * y));
        if (d <= 1)
            circle++;
    }
}

int main(int argc, char *argv[])
{
	//int iterations = atoll(argv[1]);
	long long iterations = 0;
	//printf("Ingrese el n de iteraciones\n");
    scanf("%lld", &iterations);
    double pi;
    srand(time(NULL));
    
    clock_t begin = clock();//Iniciar el tiempo
    monte_carlo(iterations);
    pi = 4.0 * circle / (double)iterations;
    clock_t end = clock();//Finalizar el tiempo
    double time_spent = ((double)(end - begin) /  CLOCKS_PER_SEC);
    printf("Pi: %f\n", pi);
    printf("tiempo = %.6f\n",time_spent);
    return 1;
}
