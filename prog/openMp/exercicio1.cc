#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 5

int main() {
    int mensagem = 5;  // Valor inicial da mensagem
    int i;

    #pragma omp parallel num_threads(NUM_THREADS) private(i)
    {
        int rank = omp_get_thread_num();
        int dest = (rank + 1) % NUM_THREADS;

        for (i = mensagem; i > 0; --i) {
            if (rank == 0) {
                // Processo inicial inicia a transmissão
                printf("Thread %d enviou mensagem %d para thread %d\n", rank, i, dest);
            } else {
                // Processos subsequentes recebem e repassam a mensagem
                printf("Thread %d recebeu mensagem %d de thread %d\n", rank, i, dest);
            }

            // Barreira para garantir que todas as threads tenham concluído a impressão antes de continuar
            #pragma omp barrier

            if (i > 1) {
                // Apenas a última iteração decrementa a mensagem
                if (rank == 0) {
                    mensagem--;
                }

                // Repassa a mensagem para o próximo processo
                #pragma omp single
                {
                    printf("Thread %d enviou mensagem %d para thread %d\n", rank, mensagem, dest);
                }

                // Barreira para garantir que todas as threads tenham concluído o envio antes de continuar
                #pragma omp barrier
            }
        }
    }

    return 0;
}
