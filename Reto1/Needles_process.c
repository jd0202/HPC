#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>


#define MAX_PROCESS 8
#ifndef MPI
#define M_PI 3.14159265358979323846
#endif

void needles(double *adds, double l, long long iterations, long long iter_per_process, int process)
{
    double x, theta, n;
    adds[process] = 0;
    for (long long i = 0; i < iter_per_process; i++)
    {
        x = (double)rand() / (double)(RAND_MAX / l);
        theta = (double)rand() / (double)(RAND_MAX / M_PI);
        n = sin(theta) / 2.0;
        if (x + n >= l || x - n <= 0)
            adds[process] = adds[process] + 1;
    }
    if (process == 0)
    {
        double alot = iterations % MAX_PROCESS;
        for (int i = 0; i < alot; i++)
        {
            x = (double)rand() / (double)(RAND_MAX / l);
            theta = (double)rand() / (double)(RAND_MAX / M_PI);
            n = sin(theta) / 2.0;
            if (x + n >= l || x - n <= 0)
                adds[process] = adds[process] + 1;
        }
    }
}


long long monte_carlo(pid_t *forks, double *adds, double l, long long iterations)
{
    long long add = 0;
    long long iter_per_process = iterations / MAX_PROCESS;
    int status = 0;
    for (int i = 0; i < MAX_PROCESS; i++)
    {
        if ((forks[i] = fork()) < 0)
        {
            perror("fork");
            abort();
        }
        else if (forks[i] == 0)
        {
            needles(adds, l, iterations, iter_per_process, i);
            exit(0);
        }
    }
    for (int i = 0; i < MAX_PROCESS; i++)
        wait(NULL);
    for (int i = 0; i < MAX_PROCESS; i++)
        add = add + adds[i];
    return add;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    double l = 1;
    int iterations = atoll(argv[1]);
    //printf("ingrese el valor de n\n");
    //scanf("%d", &iterations);
    double p, pi;
    long long n_crossed;
    double *adds = NULL;
    adds = (double *)mmap(NULL, sizeof(double *) * MAX_PROCESS, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 1, 0);
    pid_t *forks = (pid_t *)malloc(MAX_PROCESS * sizeof(pid_t));
    clock_t start = clock();
    n_crossed = monte_carlo(forks, adds, l, iterations);
    p = n_crossed / (double)iterations;
    pi = 2.0 / (p * l);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\nPi: %f\nTiempo %.6f\n", p, pi, seconds);
    return 0;
}
