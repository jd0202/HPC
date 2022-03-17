#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <math.h>

#define MAX_PROCESS 8

void darts(int *adds, long long iteraciones, long long iter_per_process, int process)
{
    double x, y, d;
    adds[process] = 0;
    for (long long i = 0; i < iter_per_process; i++)
    {
        x = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        y = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
        d = sqrt((x * x) + (y * y));
        if (d <= 1)
            adds[process] = adds[process] + 1;
    }

    if (process == 0)
    {
        double susctract = iteraciones % MAX_PROCESS;
        int i = 0;
        while (i < susctract)
        {
            x = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
            y = ((double)rand() / (double)(RAND_MAX / 2)) - 1;
            d = sqrt((x * x) + (y * y));
            if (d <= 1)
                adds[process] += 1;
            i++;
        }
    }
}

long long monte_carlo(pid_t *forks, int *adds, long long iterations)
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
            darts(adds, iterations, iter_per_process, i);
            exit(0);
        }
    }
    for (int i = 0; i < MAX_PROCESS; i++)
        wait(NULL);
    for (int i = 0; i < MAX_PROCESS; i++)
        add += adds[i];
    return add;
}

int main(int argc, char *argv[])
{
    long long iterations = 0;
    printf("ingrese el valor de n\n");
    scanf("%lld", &iterations);
    double pi;
    long long p_circle = 0;
    int *adds = (int *)mmap(NULL, sizeof(int *) * MAX_PROCESS, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 1, 0);
    int i, j, n_process, pid, begin, end, size_of_iterations_process, status;
    pid_t *forks = (pid_t *)malloc(MAX_PROCESS * sizeof(pid_t));
    srand(time(NULL));
    clock_t start = clock();
    n_process = 4;
    size_of_iterations_process = iterations / n_process;
    p_circle = monte_carlo(forks, adds, iterations);
    pi = 4.0 * p_circle / (double)iterations;
    clock_t end_time = clock();
    float segundos = (float)(end_time - start) / CLOCKS_PER_SEC;
    printf("Pi: %lf\nLa ejecucion ha tomado %.8f segundos\n", pi, segundos);
    return 0;
}
