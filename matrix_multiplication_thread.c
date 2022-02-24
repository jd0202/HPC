#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//Variables globales
int num_of_threads = 1;
int SIZE = 0;
int** A;
int** B;
int** C;


void seed_matrix(int size);
//void print_result();

//Funcion paralela
void *matmul(void* rank);

int main(int argc, char* argv[]){

  int n = atoi(argv[1]);
  int thread = atoi(argv[2]);
  SIZE = n;
  printf("\n\nMatriz de %i X %i \n",n,n);
  printf("\nHilos: %i \n",thread);
  num_of_threads = thread;
  
  pthread_t tid[num_of_threads];
  int i, j; 
  long rank;

  A = malloc(SIZE*sizeof(int*)); 
      for(i=0;i<SIZE;i++)
        A[i]=malloc(SIZE*sizeof(int));

  B = malloc(SIZE*sizeof(int*)); 
      for(i=0;i<SIZE;i++)
        B[i]=malloc(SIZE*sizeof(int)); 
  
  C =  malloc(SIZE*sizeof(int*)); 
      for(i=0;i<SIZE;i++)
        C[i]=malloc(SIZE*sizeof(int));

  //Lectura de matrices
  seed_matrix(SIZE);
  
  clock_t begin = clock();//Iniciar el tiempo
  //Creación de threads
  for (rank = 0; rank < num_of_threads; rank++)
     pthread_create(&tid[rank], NULL,matmul , (void*) rank);

 
  //Unión de threads
  for (rank = 0; rank < num_of_threads; rank++)
      pthread_join(tid[rank], NULL);
  
   clock_t end = clock();//Finalizar el tiempo

  double time_spent = ((double)(end - begin) /  CLOCKS_PER_SEC);
  printf("\nTiempo de paralelo: %.5f\n",time_spent);
  printf("-----------------------\n");


  //Impresión de resultado
  //print_result();
  

  //Liberación de memoria
  free(A);
  free(B);
  free(C);

  
  pthread_exit(NULL);
  return 0;
}


void *matmul(void* id_arg){
  int i,j,k;
  long  id = (long ) id_arg;
  int rows_per_thr = SIZE/num_of_threads;
  int start_index = id*rows_per_thr;
  int final_index = (id+1)*rows_per_thr;

  for(i=start_index;i<final_index;i++){
   for(j=0;j<SIZE;j++){
    for(k=0;k<SIZE;k++){
      C[i][j] += A[i][k]*B[k][j]; 
    }
   }
  }
}

void seed_matrix(int size){
  int i,j;
  FILE *file;
  file=fopen("matrices.txt", "r");
  
 //printf("\n\n Primera matriz: \n");
  for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
       if (!fscanf(file, "%i", &A[i][j])) 
           break;
       //printf("%i ",A[i][j]);
      }
       //printf("\n");
   }

  //printf("\n Segunda matriz \n");

  for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){
         if (!fscanf(file, "%i", &B[i][j])) 
             break; 
        // printf("%i ",B[i][j]); 
       }
     // printf("\n");
   }
  fclose(file);
}

/*
void print_result(){
  int i,j;
  printf("\n Matriz resultado: \n");
  for(i = 0; i < SIZE; i++){
      for(j = 0; j < SIZE; j++){ 
         printf("%i ",C[i][j]); 
       }
      printf("\n");
   }
}
*/
