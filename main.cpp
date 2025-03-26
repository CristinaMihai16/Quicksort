#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>    

using namespace std;
using namespace std::chrono;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int A[], int q, int r) {
    int x = A[q]; // Pivotul
    int s = q;    // Pozitia initiala a pivotului

    for (int i = q + 1; i <= r; i++) {
        if (A[i] <= x) {
            s++;
            swap(A[s], A[i]);
        }
    }
    swap(A[q], A[s]); // Plasam pivotul la pozitia finala
    return s;
}

void quicksort(int A[], int q, int r) {
    if (q < r) {
        int s = partition(A, q, r); // Determinam pozitia finala a pivotului
        quicksort(A, q, s - 1);     // Sortam partea stanga
        quicksort(A, s + 1, r);     // Sortam partea dreapta
    }
}

int main() {
    int A[2500];

    // Initializam generatorul de numere aleatorii
    srand(time(nullptr)); 


    for (int i = 0; i <1700; i++) {
        A[i] = rand() % 10001; 
    }

    int n = sizeof(A) / sizeof(A[0]);

    cout << "Array initial: ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;

    auto t1 = high_resolution_clock::now();

    quicksort(A, 0, n - 1);

    auto t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(t2 - t1);  

    cout << "Array sortat: ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;

    cout << "Timpul de rulare: " << duration.count() << " microsecunde" << endl;

    return 0;
}
