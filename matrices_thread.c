
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int **a;
int **b;
int **c;
int n;
int n_hilos=2;


// Inicializar la matriz dinámica
int **initialarray(int n)
{
    int i, j;

    int **m = NULL;

    m = (int **)calloc(n, sizeof(int *));

    for (i = 0; i < n; i++)
        *(m + i) = (int *)calloc(n,sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            *(*(m + i) + j) = rand() % 11;
    return m;
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

void **multiplyRow(void* param_arg)
{
	int id = (int) param_arg;
	int i,j,k;
	int rows_per_thr = n/n_hilos;
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
void **multiplyarray(int n)
{
    int i;
    // Construir matriz C
    c = (int **)calloc(n, sizeof(int *)); // Toma el número de filas en una matriz
    
    for (i = 0; i < n; i++)
        *(c + i) = (int *) calloc(n, sizeof(int));
	
    
    pthread_t hilos[n_hilos];

    	
	clock_t begin = clock();//Iniciar el tiempo
    // Calcular c matriz a * b = c;
    for (i = 0; i < n_hilos; i++)
    {
    	/*for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                *(*(c + i) + j) += (*(*(a + i) + k)) * (*(*(b + k) + j)); // k es el signo de la suma
        */
        pthread_create(&hilos[i], NULL, multiplyRow, (void*) i);
	}
	
	
	for (i = 0; i < n_hilos; i++)
      pthread_join(hilos[i], NULL);
	
    
    clock_t end = clock();//Finalizar el tiempo
    double time_spent = ((double)(end - begin) /  CLOCKS_PER_SEC);
    
    printf("tiempo = %.5f\n",time_spent);
    
    //pthread_exit(NULL);
    
}
//Programa principal
int main()
{
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
    
    
    multiplyarray(n);
    //outputarray(c, n);
    pthread_exit(NULL);
    
    return 0;
}
