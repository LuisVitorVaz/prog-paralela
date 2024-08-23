#include <omp.h>
#include <stdio.h>
using namespace std ;

int a[1000000], b[1000000];
//int c[1000000] ;
int  i, j, tid , somaA = 0, somaB=0, nthreads ;

int main( )
{
   for (i = 0; i < 1000000; i++){
      a[i] = 1 ;
      b[i] = 2 ;
      }
//omp_set_num_threads (3) ;

#pragma omp parallel private (tid, i) num_threads (3)
{
  nthreads = omp_get_num_threads (); // o numero de thread em execucao
  printf("O numero de threads eh = %d\n", nthreads);
  tid = omp_get_thread_num(); // retorna o rank
  if (tid == 1) {
     for (i = 0; i < 1000000; i++){
         somaA = somaA + a[i] ;
         }
       printf(" Sou a thread %d e a soma de A eh = %d\n", tid, somaA);
      }
  else {
      if (tid == 2) {
          for (j = 0; j< 1000000; j++){
               somaB = somaB + b[j] ;
          }
       printf(" Sou a thread %d e a soma de B eh = %d\n", tid, somaB);
      }
  }
 
}
   printf(" Sou a Master thread\n") ;

   printf("Soma Total %d\n", somaA+somaB) ;
}