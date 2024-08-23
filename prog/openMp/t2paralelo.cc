#include <stdio.h>
#include <time.h>
#include <omp.h>

#define vetor_size 1000000

int main() {
    clock_t start_time, end_time;

    // Declaração do vetor
    int vetor[vetor_size];

    start_time = clock();

    // Preenchimento paralelo do vetor com valores sequenciais usando OpenMP
    #pragma omp parallel for
    for(int i=0;i<vetor_size;i++)
    {
    for (int i = 0; i < vetor_size; ++i) {
        vetor[i] = i + 1;
    }
    }

    end_time = clock();

    // Cálculo do tempo de execução
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Execution Time: %f seconds\n", execution_time);

    return 0;
}
