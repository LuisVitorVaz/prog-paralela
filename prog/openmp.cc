#include <iostream>
using namespace std;
int main()
{
#pragma omp parallel
{
cout << "Hello World!\n";
}
}