#include <stdio.h>
#include "mpi.h"

int main(int argc,char* argv[])
{
int my_rank;
int proc_n;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
MPI_Comm_size(MPI_COMM_WORLD,&proc_n);
printf("meu id  %d \n",my_rank);
printf("numero de processos: %d\n",proc_n);
MPI_Finalize();
}