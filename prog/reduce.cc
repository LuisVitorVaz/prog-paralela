#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_vector[5];   // Vetor local para cada processo
    int *global_vector = NULL;  // Vetor global após a redução
    int vector_size = 5;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Preenche o vetor local com valores no processo atual
    for (int i = 0; i < 5; i++) {
        local_vector[i] = (rank + 1) * (i + 1); // Valores diferentes para cada processo
    }

    // Transmitir o tamanho do vetor para todos os processos
   // MPI_Bcast(&vector_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Alocar espaço para o vetor global apenas no processo raiz (rank 0)
    if (rank == 0) {
        global_vector = (int *)malloc(vector_size * sizeof(int));
    }
    // Cada processo imprime o vetor que recebeu
    printf("Processo %d: Vetor local: ", rank);
    for (int i = 0; i < vector_size; i++) {
        printf("%d ", local_vector[i]);
    }
    printf("\n");

    // Realiza a redução dos vetores locais em um vetor global somando os elementos
    MPI_Reduce(local_vector, global_vector, vector_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Somente o processo raiz (rank 0) imprime o vetor global após a redução
        printf("Resultado global da soma dos vetores: ");
        for (int i = 0; i < vector_size; i++) {
            printf("%d ", global_vector[i]);
        }
        printf("\n");
        // Libera a memória alocada no processo raiz
        free(global_vector);
    }

    MPI_Finalize();
    return 0;
}
