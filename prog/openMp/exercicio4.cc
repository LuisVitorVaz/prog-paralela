#include <omp.h>
#include <iostream>

static long num_steps = 100000;
double step;
int main ()
{ 
 #pragma omp parallel 
 {
     int num_steps = 100; // Substitua pelo número desejado de passos
    int i;
    double x, pi, sum = 0.0, step;

    step = 1.0 / (double)num_steps;

    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        // atomic garante que enquanto 1 thread esta acessando a regiao critica outra nao pode acessar a mesma
        #pragma omp atomic//critical // garante que so uma thread por vez acesse a regiao
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    printf("thead %d \n",omp_get_thread_num());
    printf("Valor aproximado de pi: %f\n", pi);
 }
}

