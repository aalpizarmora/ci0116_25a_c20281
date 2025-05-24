#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "SinglyLinkedList.hpp"

int main() {
    const int n = 1000000;
    // Number of nodes to insert

    const int o = 10000;
    // Number of searches and removals

    const int range = 3 * n;
    // Range of values from 0 to 3*n - 1

    // Seed the random number generator with current time
    std::srand(std::time(nullptr));

    // 1. Create an empty list and insert n random values
    SLList<int> list;

    std::cout << "Se insertan " << n << " nodos." << std::endl;
    auto start_insert = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        list.insert(i);  // Insertar en orden ascendente
    }

    /*
    for (int i = 0; i < n; ++i) {
        int random_value = std::rand() % range;
        list.insert(random_value);
        // Insert random value into the list
    }
        */
    // Insert random values into the list

    auto end_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time = end_insert - start_insert;
    std::cout << "Tiempo de inserción: " << insert_time.count() << " s" << std::endl;

    // 2. Searches of random values and measure time
    std::cout << "Se realizan " << o << " búsquedas." << std::endl;
    auto start_search = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < o; ++i) {
        int random_value = std::rand() % range;
        list.search(random_value); 
        // Search for random_value in the list
    }

    auto end_search = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> search_time = end_search - start_search;
    std::cout << "Tiempo total de búsquedas: " << search_time.count() << " s" << std::endl;

    // 3. Removals of random values and measure time
    std::cout << "Se realizan " << o << " eliminaciones." << std::endl;
    auto start_remove = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < o; ++i) {
        int random_value = std::rand() % range;
        list.remove(random_value);
        // Remove random value from the list (if it exists)
    }

    auto end_remove = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> remove_time = end_remove - start_remove;
    std::cout << "Tiempo total de eliminaciones: " << remove_time.count() << " s" << std::endl;

    return 0;
}
