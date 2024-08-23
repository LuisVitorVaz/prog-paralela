#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int array[5];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Preenche o array com valores no processo raiz.
        for (int i = 0; i < 5; i++) {
            array[i] = i * 2;
        }
    }

    // Broadcast do array a partir do processo raiz (rank 0) para todos os outros.
    MPI_Bcast(array, 5, MPI_INT, 0, MPI_COMM_WORLD);

// variavel tamanho dos dados: arry ;tipo dos dados quem ta fazendo o bcast int 5
// e o grupo de comunicacao
    // Cada processo imprime os valores do array após o broadcast.
    printf("Processo %d: Valores do array: ", rank);
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
