#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#define SIZE 300
using namespace std;

int sum = 0;
int nums[SIZE];

int main()
{
omp_set_num_threads (3) ;
for(int i = 0; i < SIZE; i++) {
  nums[i] = 1 ;
}
// criação de uma região paralela
#pragma omp parallel // cria varias em paralelo
{
  // declarada dentro da região paralela, logo privada à thread
  double sumt = 0;
  for(int i = 0; i < SIZE; i++) {
    sumt += nums[i];
  }
  // região crítica; apenas uma thread a executa em cada momento
  #pragma omp critical // executa uma por vez
  sum += sumt;
}
printf("Resultado da soma: %d\n", sum) ;

}