#include <omp.h>
#include <iostream>

using namespace std;

int main() {
    int a[1000000], b[1000000];
    // ... inicialização dos arrays a e b;

    int c[1000000];

#pragma omp parallel for
    for (int i = 0; i < 1000000; ++i) {
        int a_val = (i > 0) ? a[i - 1] : 0;
        int b_val = (i < 999999) ? b[i + 1] : 0;
    }
    // ... processamento adicional com o array c

    return 0;
}
