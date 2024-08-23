#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std ;
int tid, tid0, tid1, tid2, tid3, tid4, tid5, tid6, tid7,n ;

void paralelismo () {
omp_set_num_threads (8) ; // seta quantas trheads podem ser criadas
#pragma omp parallel private (n, tid ) // private -> serve para que cada uma tenha uma copia sem se compartilhada
{
n = omp_get_num_threads () ; // retorna o numero da thread em execução
printf ("Numero Threads: %d\n", n);
tid = omp_get_thread_num () ; // e o rank 
if (tid == 0) cout << "Sou a thread 0, a Master  !\n";
if (tid == 1) cout << "Sou a thread 1 !\n";
if (tid == 2) cout << "Sou a thread 2 !\n";
if (tid == 3) cout << "Sou a thread 3 !\n";
if (tid == 4) cout << "Sou a thread 4 !\n";
if (tid == 5) cout << "Sou a thread 5 !\n";
if (tid == 6) cout << "Sou a thread 6 !\n";
if (tid == 7) cout << "Sou a thread 7 !\n";

}
}

int main()
{
  paralelismo () ;
  cout << "Master Thread!\n";
  
}