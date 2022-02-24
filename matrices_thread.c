
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


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

void **multiplyRow(int **a, int **b, int **c, int n,int n_thr,long id)
{
	
	int i,j,k;
	int rows_per_thr = n/n_thr;
	int start_index = id*rows_per_thr;
	int final_index = (id+1)*rows_per_thr;
	
	  for(i=start_index;i<final_index;i++){
	   for(j=0;j<n;j++){
	    for(k=0;k<n;k++){
	      c[i][j] += a[i][k]*b[k][j]; 
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
	
	
	int n_hilos=16;
    
    pthread_t hilos[n_hilos];
    	
	struct timespec antes;
	clock_gettime(CLOCK_MONOTONIC, &antes);
    // Calcular c matriz a * b = c;
    for (i = 0; i < n_hilos; i++)
    {
    	/*for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                *(*(c + i) + j) += (*(*(a + i) + k)) * (*(*(b + k) + j)); // k es el signo de la suma
        */
        pthread_create(&hilos[i], NULL, multiplyRow(a,b,c,n,n_hilos,i), NULL);
	}
	
	
	
	
	
    
    struct timespec despues;
    clock_gettime(CLOCK_MONOTONIC, &despues);
    
    printf("%f sec, %ld nanosec elapsed \n", despues.tv_sec-antes.tv_sec,despues.tv_nsec-antes.tv_nsec);
    
    
    return c;
}
//Programa principal
int main()
{
    int n;

    int **a, **b, **c;
    // Arreglar un
    printf("Ingrese el n de filas y columnas\n");
    srand(time(NULL));
    scanf("%d", &n);
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
