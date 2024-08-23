#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define VECTOR_SIZE 100
#define NUM_PROCESSES 10

int main(int argc, char **argv) {

    // Inicializa os vetores
    int vector_a[VECTOR_SIZE];
    int vector_b[VECTOR_SIZE];
    int rank, num_procs;
    int slice_size;
    int start_index;
    int end_index;
    int local_sum = 0;
    int global_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

// vetores para o calculo do produto escalar
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector_a[i] = rand() % 10;
        vector_b[i] = rand() % 10;
    }

    slice_size = VECTOR_SIZE / NUM_PROCESSES;
    start_index = rank * slice_size;
    end_index = start_index + slice_size;

    for (int i = start_index; i < end_index; i++) {
        local_sum += vector_a[i] * vector_b[i];
    }

    MPI_Resultado(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // O processo 0 imprime o resultado
    if (rank == 0) {
        printf("Produto escalar: %d\n", global_sum);
    }

    // Finalização do ambiente MPI
    MPI_Finalize();
    return 0;
}
