#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
int tid ;
omp_set_num_threads (3) ;
#pragma omp parallel private (tid ) 
{
  #pragma omp sections
  {
    
    #pragma omp section
    {
     tid = omp_get_thread_num () ;
     printf("Hello World! from section 1 %d\n", tid ) ; // apenas uma thread
    }
    #pragma omp section
    {
     tid = omp_get_thread_num () ;
     printf("Hello World! from section 2 %d\n", tid ) ; // apenas uma thread
    }
         
    #pragma omp section
    {
     tid = omp_get_thread_num () ;
     printf("Hello World! from section 3 %d\n", tid ) ; // apenas uma thread
    }
  }
 }
 tid = omp_get_thread_num () ;
 printf("Hello World! from master %d\n", tid ) ; // apenas a thread master
}