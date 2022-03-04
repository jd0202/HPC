#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

void create_matrix(int size, double *matrix)
{
    int i, j;
    int n = size;
    srand(time(NULL));
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            *(matrix + i * size + j) = rand() % 10;
        }
    }
}

void mult_matrix(double *A, double *B, double *C, int size, int begin, int end)
{
    int i, j, p;
    for (i = 0; i < size; i++)
    {
        for (j = begin; j < end; j++)
        {
            for (p = 0; p < size; p++)
            {
                *(C + i * size + j) += *(A + i * size + p) * *(A + p * size + j);
            }
        }
    }
}

void read_matrix(int size, double *matrix)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%.0lf\t", *(matrix + i * size + j));
        }
        printf("\n");
    }
    printf("-------------------------------");
    printf("\n");
}

void *create_shared_memory(size_t size)
{
    // Buffer de memoria puede ser leído y escrito
    int protection = PROT_READ | PROT_WRITE;
    /* 
        El buffer será compartido, lo que significa que otros
        procesos pueden acceder a él, pero también anónimo, lo
        que significa que procesos externos al programa no pueden
        obtener una dirección de este. Solo el proceso actual y sus
        hijos pueden usarlo
    */
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    /*
        mmap(address, size, protection, flags, fd, offset)
        Cuando la bandera "MAP_ANONYMOUS" está activada, el "fd" (file descriptor)
        es ignorado. Sin embargo, algunas implementaciones requieren que sea -1.
        El offset debe ser 0 cuando se usa la bandera "MAP_ANONYMOUS"
    */
    return mmap(NULL, size, protection, visibility, -1, 0);
}

int main(int argc, char **argv)
{
    int i, j, n, pid, begin, end, size_of_matrix_process, status;
    int size = 4;

    double *A = create_shared_memory(size * size * sizeof(double));
    double *B = create_shared_memory(size * size * sizeof(double));
    double *C = create_shared_memory(size * size * sizeof(double));

    create_matrix(size, A);
    // read_matrix(size, A);
    create_matrix(size, B);
    // read_matrix(size, B);
    clock_t start = clock();
    double spent_time = 0;
    n = 4;
    size_of_matrix_process = size / n;
    for (i = 0; i < n; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            begin = size_of_matrix_process * i;
            end = size_of_matrix_process * (i + 1);
            if (i == n - 1)
            {
                end = size;
            }
            mult_matrix(A, B, C, size, begin, end);
            // read_matrix(size, C);
            exit(0);
        }
    }
    while (n > 0)
    {
        pid = wait(&status);
        --n;
    }
    clock_t end_time = clock();
    // read_matrix(size, C);
    spent_time = (double)(end_time - start) / CLOCKS_PER_SEC;
    FILE *f = fopen("result_process.txt", "a");
    fprintf(f, "Tiempo de ejecucion: %.8f \n", spent_time);
    return 0;
}
