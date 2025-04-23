#include <ordenador.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>

void imprimirArreglo(const int* A, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << A[i] << " ";
    std::cout << "\n";
}

void actualizarArreglo(int *A, int n) {
    for (int i = 0; i < n; ++i)
        A[i] = rand() % 100; // número aleatorio de 0 a 99
}

int main() {
    Ordenador* ordenador = new Ordenador();

    int n = 100;
    int* miArray = new int[n];

    std::srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        miArray[i] = rand() % 100; // número aleatorio de 0 a 99
    }

    auto inicio1 = std::chrono::high_resolution_clock::now();
    ordenador->ordenamientoPorInserccion(miArray, n); 
    auto fin1 = std::chrono::high_resolution_clock::now();

    imprimirArreglo(miArray, n);
    std::cout << "Arreglo ordenado: ";

    std::chrono::duration<double> duracion1 = fin1 - inicio1;
    std::cout << "Tiempo de ejecución: " << duracion1.count() << " segundos" << std::endl;

    actualizarArreglo(miArray, n);

    imprimirArreglo(miArray, n);

    delete[] miArray;

    return 0;
}