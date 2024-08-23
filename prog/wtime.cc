#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_vector[5];   // Vetor local para cada processo
    int global_vector[5];  // Vetor global após a redução
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();  // Início da medição de tempo

    // Preenche o vetor local com valores no processo atual
    for (int i = 0; i < 5; i++) {
        local_vector[i] = (rank + 1) * (i + 1); // Valores diferentes para cada processo
    }

    // Realiza a operação de broadcast do vetor local para todos os processos
    // MPI_Bcast(local_vector, 5, MPI_INT, 0, MPI_COMM_WORLD);

    // Realiza a redução dos vetores locais em um vetor global somando os elementos
    MPI_Reduce(local_vector, global_vector, 5, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();  // Fim da medição de tempo

    // Cada processo imprime o vetor que recebeu
    printf("Processo %d: Vetor local: ", rank);
    for (int i = 0; i < 5; i++) {
        printf("%d ", local_vector[i]);
    }
    printf("\n");

    if (rank == 0) {
        // Somente o processo raiz (rank 0) imprime o vetor global após a redução
        printf("Resultado global da soma dos vetores: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", global_vector[i]);
        }
        printf("\n");

        // Imprime o tempo de execução
        printf("Tempo de execução: %f segundos\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
