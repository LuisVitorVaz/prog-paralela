#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MAX 100

int main(int argc, char *argv[]) {
    int meu_ranque, total_num, etiq = 0;
    int origem = 0, destino = 1;
    int numeros[MAX];
    MPI_Status estado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);

    if (meu_ranque == origem) {
        /* Envia um número aleatório de inteiros para o processo 1 */
        srand(MPI_Wtime());
        total_num = (rand() / (float) RAND_MAX) * MAX;
        /* Envia a quantidade de inteiros para o processo 1 */
        MPI_Send(numeros, total_num, MPI_INT, destino, etiq, MPI_COMM_WORLD);
        printf("Processo %d enviou %d números para 1\n", origem, total_num);
    }

    if (meu_ranque == destino) {
        /* Recebe no máximo MAX números do processo 0 */
        MPI_Recv(numeros, MAX, MPI_INT, origem, etiq, MPI_COMM_WORLD, &estado);
        /* Determina quantos números foram realmente recebidos */
        MPI_Get_count(&estado, MPI_INT, &total_num);
        /* Imprime a informação no manipulador "estado" */
        printf("Processo %d recebeu %d números. Origem da mensagem = %d, etiqueta = %d\n", destino, total_num, estado.MPI_SOURCE, estado.MPI_TAG);
    }

    MPI_Finalize();

    return 0;
}
