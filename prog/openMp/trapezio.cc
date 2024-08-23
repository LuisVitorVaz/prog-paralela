#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    /* Calcula f(x) */
    double valor;
    valor = exp(x);
    return valor;
}

int main(int argc, char *argv[]) {
    /* omp_trapezio.c */

    double integral; /* Armazena resultado da integral */
    double a = 0.0, b = 1.0; /* Limite esquerdo e direito */
    long n = 800; /* Número de Trapezoides */
    double h; /* Largura da base do Trapezóide */

    h = (b - a) / n;
    integral = (f(a) + f(b)) / 2.0;

    double t_inicio = omp_get_wtime();
    
    /* Faz a redução e escalona as iterações para as threads */
    #pragma omp parallel for reduction(+:integral) schedule(static)
    for (long i = 1; i < n; i++) {
        integral += f(a + i * h);
    }

    integral *= h;

    double t_fim = omp_get_wtime();

    printf("Com n = %ld trapezoides, a estimativa da integral de %f até %f = %.15f\n", n, a, b, integral);
    printf("Tempo: %.6f segundos com %d threads.\n", t_fim - t_inicio, omp_get_max_threads());

    return 0;
}
