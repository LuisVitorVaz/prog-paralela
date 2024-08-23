#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(int argc, char *argv[]) {
    int meu_ranque, num_procs, etiq = 0;
    int total_num, origem = 0, destino = 1;
    int numeros[MAX];
    MPI_Status estado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (meu_ranque == origem) {
        srand(MPI_Wtime());
        total_num = (rand() / (float) RAND_MAX) * MAX;
        MPI_Send(numeros, total_num, MPI_INT, destino, etiq, MPI_COMM_WORLD);
        printf("Processo %d enviou %d números para processo %d.\n", origem, total_num, destino);
    } else if (meu_ranque == destino) {
        // probe basicamente le o buffer de mensagens sem removelas
        MPI_Probe(origem, etiq, MPI_COMM_WORLD, &estado);
        MPI_Get_count(&estado, MPI_INT, &total_num);

        int* vet_num = (int*)malloc(sizeof(int) * total_num);

        MPI_Recv(vet_num, total_num, MPI_INT, origem, etiq, MPI_COMM_WORLD, &estado);

        printf("Processo %d recebeu dinamicamente %d números de %d.\n", destino, total_num, origem);

        free(vet_num);
    }

    MPI_Finalize();

    return 0;
}
