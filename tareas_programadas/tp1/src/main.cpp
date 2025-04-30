#include <ordenador.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <vector>

void imprimirArreglo(const int* A, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << A[i] << " ";
    std::cout << "\n";
}

void actualizarArreglo(int* A, int n) {
    for (int i = 0; i < n; ++i)
        A[i] = rand() % 100; // número aleatorio de 0 a 99
}

int main() {
    Ordenador* ordenador = new Ordenador();
    
    std::cout << "\n-----------------------------------------------------\n";
    std::cout << ordenador->imprimirDatosDeTarea() << std::endl;
    std::cout << "-----------------------------------------------------\n\n";

    // Tamaños de los arreglos según los requisitos
    const int tam_arreglos[] = {1000, 10000, 100000, 1000000};
    const int repeticiones = 3; // Número de repeticiones para obtener el promedio

    
    // Generar y ejecutar los algoritmos para cada tamaño
    for (int tam : tam_arreglos) {
        std::cout << "Tamaño del arreglo: " << tam << std::endl;
        double tiempoTotal = 0.0; // Variable para acumular el tiempo total

        for (int i = 0; i < repeticiones; ++i) {
            int* miArray = new int[tam];
            actualizarArreglo(miArray, tam);

            // Medir el tiempo de ejecución del algoritmo
            auto inicio = std::chrono::high_resolution_clock::now();
            //ordenador->ordenamientoPorInserccion(miArray, tam);  // Aquí cambiar por otros algoritmos
            //ordenador->ordenamientoPorSeleccion(miArray, tam);
            //ordenador->ordenamientoPorMezcla(miArray, tam);
            //ordenador->ordenamientoPorMonticulos(miArray, tam);
            //ordenador->ordenamientoRapido(miArray, tam);
            ordenador->ordenamientoPorResiduos(miArray, tam);
            auto fin = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duracion = fin - inicio;
            tiempoTotal += duracion.count(); // Acumular el tiempo

            std::cout << "Ejecución " << i + 1 << " - Tiempo de ejecución: " << duracion.count() << " segundos" << std::endl;

            // Liberar memoria del arreglo después de cada ejecución
            delete[] miArray;
        }

        // Calcular el tiempo promedio
        double tiempoPromedio = tiempoTotal / repeticiones;
        std::cout << "Tiempo promedio de ejecución: " << tiempoPromedio << " segundos" << std::endl;
        std::cout << std::endl;
    }

    delete ordenador;
    return 0;
}
