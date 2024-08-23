#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std ;
int main()
{
#pragma omp parallel // trecho onde o codigo fica em loop
{
cout << "Hello World!\n";
}
cout << " Thread master: Hello World!\n";
}