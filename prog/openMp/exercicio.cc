#include <iostream>
#include <omp.h>

int main() {
    const int n = 100; // Substitua 100 pelo tamanho desejado do vetor

    // Declare os vetores
    double a[n], b[n], c[n], d[n], e[n], f = 2.0, z[n];

    // Inicialize os vetores b, c e e (substitua conforme necessário)
    for (int i = 0; i < n; i++) {
        b[i] = i;
        c[i] = i * 2;
        e[i] = i * 3;
    }

    #pragma omp parallel
    {
        #pragma omp for nowait // faz com que nao seja preciso esperar o fim de uma processo para comecar o outro
        for (int j = 0; j < n; j++) {
            a[j] = b[j] + c[j];
        }
        printf("Thread %d fez o primeiro for\n", omp_get_thread_num());

        #pragma omp for nowait
        for (int j = 0; j < n; j++) {
            d[j] = e[j] * f;
        }
        printf("Thread %d fez o segundo for\n", omp_get_thread_num());

        #pragma omp for nowait
        for (int j = 0; j < n - 1; j++) {
            z[j] = (a[j] + a[j + 1]) * 0.5;
        }
        printf("Thread %d fez o terceiro for\n", omp_get_thread_num());

        // Último elemento de z
        z[n - 1] = a[n - 1];
    }

    // Imprimir os resultados ou fazer algo com os vetores a, d e z
    printf("Fez todos os fors\n");

    return 0;
}
