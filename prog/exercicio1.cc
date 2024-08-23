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
#define MAX 10000
int main(int argc, char *argv[]) {
    int rank, process;
    int *vet,*local;
    // MPI_Status status;
    // MPI_Init(&argc, &argv);
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    // MPI_Comm_size(MPI_COMM_WORLD, &process);

    // if(rank ==0)
    // {
    //     vet=(int*)malloc(sizeof(int)*MAX);
    //     for(i=0;i<MAX;i++)
    //     {
           
    //         vet[i]=i+1;
    //     }
    // }
    // // int partvet = MAX / process; // vetor local
    // local=(int*)malloc(sizeof(int)*MAX);
    // MPI_Scatter(vet,partvet,MPI_INT,local,partvet,MPI_INT,0,MPI_COMM_WORLD);
// printf("meu numero e %d",rank);
// for(i=0;i<partvet;i++)
// {
//      printf("%d",local[i]);
// }

    // if (rank == 0) {
    //     for (int i = 0; i < n - 1; i++)
    //     {
    //         for (int j = 0; j < n - i - 1; j++)
    //         {
    //             if(vet[j] > vet[j + 1])
    //             {
    //             // Troca os elementos se estiverem fora de ordem
    //             temp = vet[j];
    //             vet[j] = vet[j + 1];
    //             vet[j + 1] = temp;
    //             }
    //         }   
    //     }

    // }
    // MPI_Send(partvet,MPI_INT,1, 99, MPI_COMM_WORLD);
    // MPI_Recv(vet,1000, MPI_INT, 99, 0, MPI_COMM_WORLD,status);

    //     for(int i=0;i<10;i++)
    //     {
    //         printf("%d",vet[i]);
    //     }


    // MPI_Finalize();
    return 0;
}
