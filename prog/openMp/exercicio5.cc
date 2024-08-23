#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
// Remova o modificador static para pi
double pi;

int main() {
    // int num_steps = 100; // Remova ou renomeie para evitar sombreamento

    int i;
    double x, step;
    double sum = 0.0;

    step = 1.0 / (double)num_steps;

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    #pragma omp critical // critical todas as variaveis vao acessar porem somente um por vez e possivel

    {
        pi = step * sum;
        printf("Thread %d\n", omp_get_thread_num());
        printf("Valor aproximado de pi: %f\n", pi);
        printf("Soma reduzida: %f\n", pi); // Movido para a região crítica
    }

    return 0;
}
