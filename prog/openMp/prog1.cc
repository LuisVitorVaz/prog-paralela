#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
#pragma omp parallel
{
cout << "Hello World!\n";
}
}