#include <omp.h>
#include <stdio.h>
int main () {
int nthreads, tid;
/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(tid) num_threads (10)
{
/* Obtain and print thread id */
tid = omp_get_thread_num();
printf("Hello World from thread = %d\n", tid);
/* Only master thread does this */
if (tid == 0){
    nthreads = omp_get_num_threads();
    printf("Thread Master: Number of threads = %d\n", nthreads);
}
} /* All threads join master thread and terminate */
printf("thread Master %d\n", tid );
}