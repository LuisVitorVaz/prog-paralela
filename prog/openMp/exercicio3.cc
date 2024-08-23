#include <omp.h>
#include <iostream>

int main() {
    const int n = 10; // Substitua 10 pelo tamanho desejado do vetor 'a'

    // Declare os vetores
    double a[n];

    // Inicialize o vetor 'a' (substitua conforme necessário)
    for (int i = 0; i < n; i++) {
        a[i] = 1;
    }

    #pragma omp parallel num_threads(n)
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < n; i++) {
            a[i] = 1.0;
            printf("Thread %d atualizou a[%d] para %f\n", tid, i, a[i]);
        }
    }

    // Imprimir os resultados ou fazer algo com o vetor 'a'
    std::cout << "Valores finais do vetor 'a':" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "a[" << i << "] = " << a[i] << std::endl;
    }

    return 0;
}
