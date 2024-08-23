#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000000

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cria o vetor com valores aleatórios no processo raiz (rank 0)
    int *array = NULL;
    if (rank == 0) {
        array = (int*)malloc(ARRAY_SIZE * sizeof(int));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = i+1;  // Preencha o vetor com valores aleatórios.
        }
    }
    // Valor a ser procurado no vetor
    int valor = 100000;

    double startTime = MPI_Wtime();

    int achou = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] == valor) {
            achou = 1;
            break;
        }
    }

    double endTime = MPI_Wtime();

    // Processo raiz (rank 0) exibe o resultado e o tempo de busca
    if (rank == 0) {
        if (achou) {
            printf("Valor %d encontrado no vetor.\n", valor);
        } else {
            printf("Valor %d NÃO encontrado no vetor.\n", valor);
        }
        printf("Tempo de busca: %f segundos\n", (endTime - startTime)*10000);
    }

    MPI_Finalize();
}
