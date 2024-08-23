#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std ;
int main()
{
int id, n = 20 ;
omp_set_num_threads(4);
#pragma omp parallel firstprivate (n)
 {
  cout << "Hello World!!" << n << endl;
  id = omp_get_thread_num();
  cout << "Sou a thread  " << id << endl;
 }
cout << "Master thread Hello World!\n";
}