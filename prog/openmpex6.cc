#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

int main() {
#pragma omp parallel
{
    cout << "Todos os threads executam isso\n";

#pragma omp sections
    {
#pragma omp section
        {
            cout << "Isso é executado em paralelo\n";
        }

#pragma omp section
        {
            cout << "Declaração sequencial 1\n";
            cout << "Isso sempre é executado após a declaração 1\n";
        }

#pragma omp section
        {
            cout << "Isso também é executado em paralelo\n";
        }
    }
}

    return 0;
}
