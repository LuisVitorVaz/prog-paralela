#include <iostream>
#include <omp.h>

int main() {
    const int size = 100;
    int sharedVar = 0;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        #pragma omp atomic
        sharedVar += 1;  // Incremento atomicamente
    }

    std::cout << "Valor final da variável compartilhada: " << sharedVar << std::endl;

    return 0;
}
