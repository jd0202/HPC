#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


long long monte_carlo(long long iterations)
{
    double x, y, d;
    long long circle = 0;
	long long i = 0;
    for (i = 0; i < iterations; i++)
    {
        x = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        y = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        d = sqrt((x * x) + (y * y));
        if (d <= 1)
            circle++;
    }
    return circle;
}

int main(int argc, char *argv[])
{
	int iterations = atoll(argv[1]);
	//printf("Ingrese el n de iteraciones\n");
    //scanf("%d", &iterations);
    float pi;
    long long circle = 0;
    srand(time(NULL));
    
    
    clock_t begin = clock();//Iniciar el tiempo
    circle = monte_carlo(iterations);
    pi = 4.0 * circle / (double)iterations;
    clock_t end = clock();//Finalizar el tiempo
    double time_spent = ((double)(end - begin) /  CLOCKS_PER_SEC);
    printf("Pi: %f\n", pi);
    printf("tiempo = %.6f\n",time_spent);
    return 1;
}
