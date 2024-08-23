#include <iostream>
#include <omp.h>

int main() {
    const int size = 10;
    int arr[size];

    // Inicializa o array
    for (int i = 0; i < size; i++)
        arr[i] = size - i;

    #pragma omp parallel
    {
        // Não há necessidade de esperar aqui, pois usamos a cláusula 'nowait'
        #pragma omp for nowait
        for (int i = 0; i < size / 2; i++) {
            arr[i] = arr[i] * 2;
            std::cout << "Thread " << omp_get_thread_num() << " processou o índice " << i << std::endl;
        }

        #pragma omp for // diferenca para omp paralel for e que aqui nao cria novas threads porem o palalel cria 
        for (int i = size / 2; i < size; i++) {
            arr[i] = arr[i] * 2;
            std::cout << "Thread " << omp_get_thread_num() << " processou o índice " << i << std::endl;
        }
    }

    // A execução continua aqui sem esperar a conclusão de todas as threads

    std::cout << "Array depois da paralelização:\n";
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}
