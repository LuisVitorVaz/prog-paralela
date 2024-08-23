// exercicio 3 
// ciar um vetor grande com número aleatórios
// distribuir o vetor entre os ranks
// fazer um burble sorte em cada rank
// reagrupar o vetor de forma que fique organizado: 
// na hora a junção o vetor resultando é montado por 
// cada elemento mínimo atual do vetor

#include <stdio.h>
#include "mpi.h"
#include <limits.h>
#include<stdlib.h>
int i;
#define MAX 100
void bubbleSort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++)
       for (int j = 0; j < n - i - 1; j++)
          if (arr[j] > arr[j + 1]) {
            // troca os elementos
            int temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
}
int main(int argc, char *argv[]) {
    int rank, process;
    int temp;
    int *vet,*local,*novo,*vetorfinal;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &process);

    if(rank ==0)
    {
        vet=(int*)malloc(sizeof(int)*MAX);
        novo=(int*)malloc(sizeof(int)*MAX);
        vetorfinal=(int*)malloc(sizeof(int)*MAX);
        for(i=0;i<MAX;i++)
        {
           
            vet[i]=10-i;
        }
    }
     int partvet = MAX / process; // vetor local
    local=(int*)malloc(sizeof(int)*MAX);
    MPI_Scatter(vet,partvet,MPI_INT,local,partvet,MPI_INT,0,MPI_COMM_WORLD);
// printf("\n meu numero e %d \n",rank);
//   for(i=0;i<partvet;i++)
//         {
//             printf("%d ",local[i]);
//         }
//         printf("\n \n");
         
 bubbleSort(local,partvet); 
//   for(i=0;i<partvet;i++)
//         {
//             printf("%d ",local[i]);
//         }
//          printf("\n \n");
        MPI_Gather(local,partvet,MPI_INT,novo,partvet,MPI_INT,0,MPI_COMM_WORLD);
if(rank==0)
{
    for (i=0;i<MAX;i++)
    {
        if(novo<vet)
        {
            vetorfinal[i]=vet[i];
        }
    }
    
 for(i=0;i<MAX;i++)
        {
            
            printf("%d ",novo[i]);
        }
         printf("\n \n");
}

                // }
    // MPI_Send(partvet,MPI_INT,1, 99, MPI_COMM_WORLD);
    // MPI_Recv(vet,1000, MPI_INT, 99, 0, MPI_COMM_WORLD,status);

    //     for(int i=0;i<10;i++)
    //     {
    //         printf("%d",vet[i]);
    //     }


    MPI_Finalize();
    return 0;
}
