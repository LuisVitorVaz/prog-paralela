#include <stdio.h>
#include <omp.h>

int main() {
    int sharedVariable = 0;

    #pragma omp parallel num_threads(2)
    {
        int threadID = omp_get_thread_num();

        #pragma omp critical
        {
            sharedVariable += 1;
            printf("Thread %d: sharedVariable = %d\n", threadID, sharedVariable);
        }

        #pragma omp flush(sharedVariable)// forca com que as threads sejam atulizadas

        // Outras operações que não precisam de sincronização explícita

        // A diretiva flush garante que as atualizações feitas por uma thread sejam visíveis para outras
    }

    return 0;
}
