#include <stdio.h>
#include <math.h>
#include "mpi.h"

double f(double x) {
    double return_val;
    return_val = exp(x); /* Função exponencial */
    return return_val;
}

int main(int argc, char *argv[]) {
    int meu_ranque, num_procs; /* respectivamente q e p */
    double a = 0.0, b = 1.0; /* Limites da integral */
    double tempo_inicial, tempo_final; /* Tempo de execução */
    long int n = 100000000; /* Número de trapezoides */

    double x, h; /* x é a base do trapezoide */
    double integral = 0.0, total; /* Integral de cada processo e total */
    int origem, destino = 0; /* Origem e destino das mensagens */
    int etiq = 3; /* Uma etiqueta qualquer */

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* h é o mesmo para todos os processos */
    h = (b - a) / n;

    /* O processo 0 calcula o valor de f(x)/2 em a e b */
    if (meu_ranque == 0) {
        tempo_inicial = MPI_Wtime();
        integral = (f(a) + f(b)) / 2.0;
    }

    /* Cada processo calcula a integral sobre n/num_procs trapezoides */
    for (x = a + (meu_ranque + 1) * h; x < b; x += num_procs * h) {
        integral += f(x);
    }
    integral = integral * h;

    /* O processo 0 soma as integrais parciais recebidas */
    if (meu_ranque == 0) {
        total = integral;
        for (origem = 1; origem < num_procs; origem++) {
            MPI_Recv(&integral, 1, MPI_DOUBLE, origem, etiq, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += integral;
        }
    } else {
        /* As integrais parciais são enviadas para o processo 0 */
        MPI_Send(&integral, 1, MPI_DOUBLE, destino, etiq, MPI_COMM_WORLD);
    }

    /* Imprime o resultado */
    if (meu_ranque == 0) {
        tempo_final = MPI_Wtime();
        printf("Foram gastos %f segundos\n", tempo_final - tempo_inicial);
        printf("Com n = %ld trapezoides, a estimativa da integral de %f até %f = %f\n", n, a, b, total);
    }

    MPI_Finalize();

    return 0;
}
