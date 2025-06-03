#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "ChainedHashTable.hpp"

//#include "BinarySearchTree.hpp"
//#include "SinglyLinkedList.hpp"

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
    // or a  RBTree<int> tree;
    // BSTree<int> tree;
    ChainedHashTable<int> table(n);
    

    std::cout << "Se insertan " << n << " nodos." << std::endl;
    std::chrono::high_resolution_clock::time_point start_insert = std::chrono::high_resolution_clock::now();

    //tree.fastInsert(n);


    for (int i = 0; i < n; ++i) {
        table.insert(i);  // Insertar en orden ascendente
    }

    /*for (int i = 0; i < n; ++i) {
        int random_value = std::rand() % range;
        tree.insert(random_value);
        // Insert random value into the list
    } */
    
    // Insert random values into the list

    std::chrono::high_resolution_clock::time_point end_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time = end_insert - start_insert;
    std::cout << "Tiempo de inserción: " << insert_time.count() << " s" << std::endl;

    // 2. Searches of random values and measure time
    std::cout << "Se realizan " << o << " búsquedas." << std::endl;
    auto start_search = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < o; ++i) {
        int random_value = std::rand() % range;
        table.search(random_value);
        //tree.search(tree.getRoot(), random_value);
        // needs a root node to search 
        // Search for random_value in the list
    }

    std::chrono::high_resolution_clock::time_point end_search = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> search_time = end_search - start_search;
    std::cout << "Tiempo total de búsquedas: " << search_time.count() << " s" << std::endl;

    
    std::chrono::high_resolution_clock::time_point start_remove = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < o; ++i) {
        int random_value = std::rand() % range;
        table.remove(random_value);
        //tree.remove(random_value);
        // Remove random value from the list (if it exists)
    }
    std::chrono::high_resolution_clock::time_point end_remove = std::chrono::high_resolution_clock::now();
    
    // 3. Removals of random values and measure time
    std::cout << "Se realizan " << o << " eliminaciones." << std::endl;
    std::chrono::duration<double> remove_time = end_remove - start_remove;
    std::cout << "Tiempo total de eliminaciones: " << remove_time.count() << " s" << std::endl;

    return 0;
}
