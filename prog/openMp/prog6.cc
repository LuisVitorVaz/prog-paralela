#include <omp.h>
#include <stdio.h>
using namespace std ;

int a[10] ={0,0,0,0,0,0,0,0,0,0}, b[10] ={0,0,0,0,0,0,0,0,0,0};
int c[10]= {0,0,0,0,0,0,0,0,0,0}, i=0, x, tid, nthreads ;

int main( )
{
  omp_set_num_threads(3);
#pragma omp parallel firstprivate (i) private (x, tid)
{
  x = omp_get_num_threads ();
  printf("O numero de threads eh = %d\n", x);
  tid = omp_get_thread_num () ;
     if ( tid == 0){
        a[0]=0;
            for (i = 1; i < 10; i++){a[i] = a[i] +1 ;}
    }
     if ( tid == 1) {
        b[0]=0;
             for (i = 1; i < 10; i++){b[i] = b[i] + 2 ;}
    }
     if ( tid == 2) {
        c[0]=0;
        for (i = 1; i < 10; i++){c[i] = c[i] + 3 ;}

    }
  }
  for (i = 0; i < 10; i++){
    printf("a[%d] = %d ", i, a[i]) ;
  }

  for (i = 0; i < 10; i++){
     printf("b[%d] = %d ", i, b[i]) ;
  }

  for (i = 0; i < 10; i++){
    printf("c[%d] = %d ", i, c[i]) ;
  }
}