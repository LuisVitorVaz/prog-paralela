#include <iostream>
#include <omp.h>

int main() {
    const int N = 10;
    int result[N];

    #pragma omp parallel for ordered
    for (int i = 0; i < N; i++) {
        #pragma omp ordered
        {
            result[i] = omp_get_thread_num();  // Código que precisa ser executado em ordem
        }
    }

    std::cout << "Resultado do loop paralelo:\n";
    for (int i = 0; i < N; i++) {
        std::cout << "Elemento " << i << ": Thread " << result[i] << "\n";
    }

    return 0;
}
