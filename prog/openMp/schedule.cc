#include <iostream>
#include <omp.h>

int main() {
    const int N = 100;
    int result[N];

    #pragma omp parallel for schedule(static, 10) // schedule divide igualmente as tarefas
    for (int i = 0; i < N; i++) {
        result[i] = omp_get_thread_num();  // Atribui o número da thread à posição do resultado
    }

    std::cout << "Resultado do loop paralelo:\n";
    for (int i = 0; i < N; i++) {
        std::cout << "Elemento " << i << ": Thread " << result[i] << "\n";
    }

    return 0;
}
