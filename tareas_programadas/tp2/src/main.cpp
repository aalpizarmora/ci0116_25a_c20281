#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "SinglyLinkedList.hpp"

int main() {
    const int n = 1000000;  // Número de nodos a insertar
    const int e = 10000;    // Número de operaciones de búsqueda/eliminación
    const int range = 3 * n; // Rango de valores [0, 3n)
    
    // Inicializar semilla para números aleatorios
    std::srand(std::time(nullptr));
    
    // 1. Crear lista vacía e insertar n nodos con valores aleatorios
    SLList<int> list;
    
    std::cout << "Insertando " << n << " nodos..." << std::endl;
    auto start_insert = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < n; ++i) {
        int random_value = std::rand() % range;
        list.insert(random_value);
    }
    
    auto end_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time = end_insert - start_insert;
    std::cout << "Tiempo de insercion: " << insert_time.count() << " segundos" << std::endl;
    
    // 2. Realizar e búsquedas de valores aleatorios y medir el tiempo
    std::cout << "Realizando " << e << " busquedas..." << std::endl;
    auto start_search = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < e; ++i) {
        int random_value = std::rand() % range;
        list.search(random_value);
    }
    
    auto end_search = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> search_time = end_search - start_search;
    std::cout << "Tiempo total de busquedas: " << search_time.count() << " segundos" << std::endl;
    std::cout << "Tiempo promedio por busqueda: " << search_time.count()/e << " segundos" << std::endl;
    
    // 3. Realizar e eliminaciones de valores aleatorios y medir el tiempo
    std::cout << "\nRealizando " << e << " eliminaciones..." << std::endl;
    auto start_remove = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < e; ++i) {
        int random_value = std::rand() % range;
        list.remove(random_value);
    }
    
    auto end_remove = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> remove_time = end_remove - start_remove;
    std::cout << "Tiempo total de eliminaciones: " << remove_time.count() << " segundos" << std::endl;
    std::cout << "Tiempo promedio por eliminacion: " << remove_time.count()/e << " segundos" << std::endl;
    
    return 0;
}