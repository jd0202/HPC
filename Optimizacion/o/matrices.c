#include <stdio.h>
#include <stdlib.h>
#include <time.h>



// Inicializar la matriz dinámica
int **initialarray(int n)
{
    int i, j;

    int **a = NULL;

    a = (int **)calloc(n, sizeof(int *));

    for (i = 0; i < n; i++)
        *(a + i) = (int *)calloc(n,sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            *(*(a + i) + j) = rand() % 11;
    return a;
}

// Matriz de salida
void outputarray(int **a, int n)
{
    int i, j;
    int k = 0;
    printf("Output the result:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {

            printf("%d ", *(*(a + i) + j));
            k++;
            if (n == k)
            {
                printf("\n");
                k = 0;
            }
        }
    }
}
// c = a * b
int **multiplyarray(int **a, int **b, int n)
{
    int **c;
    int i, j, k;
    // Construir matriz C
    c = (int **)calloc(n, sizeof(int *)); // Toma el número de filas en una matriz
    
    for (i = 0; i < n; i++)
        *(c + i) = (int *) calloc(n, sizeof(int));
	
	clock_t begin = clock();
    // Calcular c matriz a * b = c;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                *(*(c + i) + j) += (*(*(a + i) + k)) * (*(*(b + k) + j)); // k es el signo de la suma
    
    clock_t end = clock();//Finalizar el tiempo
    double time_spent = ((double)(end - begin) /  CLOCKS_PER_SEC);
    
    //printf("tiempo = %.6f\n",time_spent);
    printf("%.6f;",time_spent);
    
    return c;
}
//Programa principal
int main(int argc, char *argv[])
{
    int n;

    int **a, **b, **c;
    // Arreglar un
    //printf("Ingrese el n de filas y columnas\n");
    srand(time(NULL));
    //scanf("%d", &n);
    n=atoll(argv[1]);
    a = initialarray(n);
    //outputarray(a, n);
    // Matriz b
    b = initialarray(n);
    //outputarray(b, n);
    // Matriz c
    
    c = multiplyarray(a, b, n);
    //outputarray(c, n);
    
    return 0;
}
