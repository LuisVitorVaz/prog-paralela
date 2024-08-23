#include <stdio.h>
#include <string.h>

#include "mpi.h"

int main(int argc,char **argv) {

    int numero, i, fat=1  ;

    int myrank, size;

    MPI_Status status;

    MPI_Init (&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if (myrank==0){

        printf("Sou o processo 0 \n");

        for(i=1; i<4; i++){

              scanf("%d", &numero);

  MPI_Send(&numero,1,MPI_INT,i,99,MPI_COMM_WORLD);

             }

        for(i=1; i<4; i++){                   MPI_Recv(&numero,1,MPI_INT,MPI_ANY_SOURCE,99,MPI_COMM_WORLD,&status);

              printf("resultado: %d \n",numero);

           }

        }

else{

     if (myrank==1){

         printf("Eu sou o processo 1 \n");

         MPI_Recv(&numero,sizeof(int),MPI_INT,0,99,MPI_COMM_WORLD,&status);

         for(i=1; i<=numero; i++) fat = fat*i ;

         MPI_Send(&fat,1,MPI_INT,0,99,MPI_COMM_WORLD);

         }

     else {

         if (myrank==2) {

             printf("Eu sou o processo 2 \n");  MPI_Recv(&numero,sizeof(int),MPI_INT,0,99,MPI_COMM_WORLD,&status);                        for(i=1; i<=numero; i++) fat = fat*i ;

             MPI_Send(&fat,1,MPI_INT,0,99,MPI_COMM_WORLD);

             }

         else{

              printf("Eu sou o processo 3 \n");

              MPI_Recv(&numero,sizeof(int),MPI_INT,0,99,MPI_COMM_WORLD,&status) ;  for(i=1; i<=numero; i++) fat = fat*i ;  MPI_Send(&fat,1,MPI_INT,0,99,MPI_COMM_WORLD) ;  }

       }

MPI_Finalize();

}

}