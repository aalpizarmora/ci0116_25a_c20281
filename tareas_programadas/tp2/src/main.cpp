#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// 1. Structures to collect data

#include "SinglyLinkedList.hpp"
// #include "BinarySearchTree.hpp"
// #include "RedBlackTree.hpp"
// #include "ChainedHashTable.hpp"
#include "Student.hpp"

int main() {
    std::cout << imprimirDatosDeTarea() << "\n\n";
    
    const int n = 1000000;   // Number of insertions
    const int o = 10000;     // Number of searches and deletions
    const int range = 3 * n; // Range for generating random values

    const bool insercion_ordenada = false;
    // 2. Set to true to insert in ascending order from 0 to n-1
    //    Set to false to insert random values

    std::srand(std::time(nullptr));  // Random seed

    // 3. Select the data structure to collect:

     std::cout << "Active structure: Singly Linked List (SLList)" << std::endl;
     SLList<int> lista;

    // std::cout << "Active structure: Binary Search Tree (BSTree)" << std::endl;
    // BSTree<int> tree;

    // std::cout << "Active structure: Red-Black Tree (RBTree)" << std::endl;
    // RBTree<int> rbtree;

    // std::cout << "Active structure: Chained Hash Table" << std::endl;
    // ChainedHashTable<int> table(n);

    // INSERTION
    std::cout << "Inserting " << n << " "
              << (insercion_ordenada ? "ordered" : "random") << " values." << std::endl;

    auto start_insert = std::chrono::high_resolution_clock::now();

    // 4. "If" structure just for Binary Search Tree
    /* if (insercion_ordenada) {
        // Fast insertion of ordered sequence
        tree.fastInsert(n);
    } else { */
        for (int i = 0; i < n; ++i) {
            int value = insercion_ordenada ? i : std::rand() % range;

            // 5. Insert the value into the selected data structure

             lista.insert(value);             // SLList
            // tree.insert(value);                 // BSTree
            // rbtree.insert(value);            // RBTree
            // table.insert(value);             // ChainedHashTable
        }
    // }
    auto end_insert = std::chrono::high_resolution_clock::now();
    std::cout << "Insertion time: "
              << std::chrono::duration<double>(end_insert - start_insert).count()
              << " s\n" << std::endl;

    // SEARCH
    std::cout << o << " random searches will be performed." << std::endl;
    auto start_search = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < o; ++i) {
        int random_value = std::rand() % range;

        // 6. Uncomment the search method for the selected data structure
               
         lista.search(random_value);                  // SLList
        // tree.search(tree.getRoot(), random_value);     // BSTree
        // rbtree.search(rbtree.getRoot(), random_value); // RBTree
        // table.search(random_value);                  // ChainedHashTable
    }
    auto end_search = std::chrono::high_resolution_clock::now();
    std::cout << "Total search time: "
              << std::chrono::duration<double>(end_search - start_search).count()
              << " s\n" << std::endl;

    // DELETION
    std::cout << o << " random deletions will be performed." << std::endl;
    auto start_remove = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < o; ++i) {
        int random_value = std::rand() % range;

        // 7. Uncomment the remove method for the selected data structure

         lista.remove(random_value);             // SLList
        // tree.remove(random_value);               // BSTree
        // rbtree.remove(random_value);           // RBTree
        // table.remove(random_value);            // ChainedHashTable
    }
    auto end_remove = std::chrono::high_resolution_clock::now();
    std::cout << "Total deletion time: "
              << std::chrono::duration<double>(end_remove - start_remove).count()
              << " s\n" << std::endl;

    return 0;
}
