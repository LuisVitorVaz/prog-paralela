#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv) {

    int numero, myrank, size;

    MPI_Status status;

    MPI_Init (&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    printf("Ola... \n");

    if (myrank==0) {

        printf("Sou o processo 0 \n");

        scanf("%d", &numero);

        MPI_Send(&numero,1,MPI_INT,1,99,MPI_COMM_WORLD);

        MPI_Recv(&numero,1,MPI_INT,2,99,MPI_COMM_WORLD,&status);

        printf("Sou o processo 0, recebi do processo 2 o valor%d \n", numero);

        }

else{

     if (myrank==1){

       printf("Eu sou o processo 1 \n");

       MPI_Recv(&numero,sizeof(int),MPI_INT,0,99,MPI_COMM_WORLD,&status);

       numero = numero + 10 ;

       MPI_Send(&numero,1,MPI_INT,2,99,MPI_COMM_WORLD);

           } 

  else{

       printf("Eu sou o processo 2 \n");

       MPI_Recv(&numero,sizeof(int),MPI_INT,1,99,MPI_COMM_WORLD,&status); 

       numero = numero + 10 ;

       MPI_Send(&numero,1,MPI_INT,0,99,MPI_COMM_WORLD);

                  } 

       }

MPI_Finalize();

}