#include <stdio.h>
#include <omp.h>
#include <cmath>  // para a função ceil

#define VECTOR_SIZE 100
#define NUM_THREADS 10
int i;
int local[NUM_THREADS] = {0};

int main() {
    int tam_vet = ceil(static_cast<double>(VECTOR_SIZE) / NUM_THREADS);
    int vet1[tam_vet];
    int vet2[tam_vet];
    int produto = 0;

    // Inicializa vetores locais para teste
    #pragma omp parallel num_threads(NUM_THREADS) private(vet1, vet2, i)
    {
        int rank = omp_get_thread_num();

        // Inicializa vetores locais para teste
        #pragma omp for reduction(+:local[rank])
        for (i = 0; i < tam_vet; i++) {
            if ((rank * tam_vet + i) < VECTOR_SIZE) {
                vet1[i] = 1;  // Exemplo de inicialização
                vet2[i] = 10;  // Exemplo de inicialização
            }
             local[rank] += vet1[i] * vet2[i];
        }
        #pragma omp critical
        {
            printf("Produtos escalares locais:\n");
            for (int i = 0; i < NUM_THREADS; ++i)
            {
                produto += local[i];
                printf("Thread %d: Produto escalar local = %d\n", i, local[i]);
            }
        }
    }

    // Imprime o resultado do produto escalar global
    printf("Produto escalar global = %d\n", produto);

    return 0;
}
