#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
using namespace std::chrono;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int A[], int q, int r) {
    int x = A[q];
    int s = q;
    for (int i = q + 1; i <= r; i++) {
        if (A[i] <= x) {
            s++;
            swap(A[s], A[i]);
        }
    }
    swap(A[q], A[s]);
    return s;
}

void quicksort(int A[], int q, int r) {
    if (q < r) {
        int s = partition(A, q, r);
        quicksort(A, q, s - 1);
        quicksort(A, s + 1, r);
    }
}

bool readFromFile(const char* filename, int*& data, int& size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului de intrare.\n";
        return false;
    }

    file >> size;
    if (size <= 0) {
        cerr << "Dimensiune invalida in fisier.\n";
        return false;
    }

    data = new int[size];
    for (int i = 0; i < size; ++i) {
        if (!(file >> data[i])) {
            cerr << "Eroare la citirea elementului " << i << ".\n";
            delete[] data;
            return false;
        }
    }
    file.close();
    return true;
}

void writeToFile(const char* filename, int* data, int size) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Eroare la scrierea in fisierul de iesire.\n";
        return;
    }

    for (int i = 0; i < size; ++i)
        file << data[i] << " ";
    file << "\n";

    file.close();
}

int main() {
    int* A = nullptr;
    int n;

    if (!readFromFile("numere5.txt", A, n)) {
        return 1;
    }

    auto t1 = high_resolution_clock::now();
    quicksort(A, 0, n - 1);
    auto t2 = high_resolution_clock::now();

    auto durata = duration_cast<milliseconds>(t2 - t1).count();

    writeToFile("output5.txt", A, n);

    cout << "Timpul de rulare: " << durata << " milisecunde\n";

    delete[] A;
    return 0;
}
