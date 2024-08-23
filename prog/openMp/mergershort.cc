#include <iostream>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                // Ordena a primeira metade
                mergeSort(arr, l, m);
            }

            #pragma omp section
            {
                // Ordena a segunda metade
                mergeSort(arr, m + 1, r);
            }
        }

        // Combina as duas metades ordenadas
        merge(arr, l, m, r);
    }
}

int main() {
    const int size = 10;
    int arr[size] = {12, 11, 13, 5, 6, 7, 8, 9, 10, 1};

    std::cout << "Array antes da ordenacao:\n";
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    // Aplica o Merge Sort paralelo
    mergeSort(arr, 0, size - 1);

    std::cout << "Array depois da ordenacao:\n";
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}
