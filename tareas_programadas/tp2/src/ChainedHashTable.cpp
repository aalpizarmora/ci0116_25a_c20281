/*
 Implementación de ChainedHashTable.cpp
 Basado en: "Introduction to Algorithms" por Cormen, Leiserson, Rivest y Stein
 Implementado por: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#include "ChainedHashTable.hpp"
#include <stdexcept>

template <typename DataType>
void ChainedHashTable<DataType>::insert(const DataType& value) {
    size_t index = value % size; // Función hash h(k) = k mod m
    table[index].insert(value); // Insertar en la lista correspondiente
}

template <typename DataType>
DLListNode<DataType>* ChainedHashTable<DataType>::search(const DataType& value) const {
    size_t index = value % size;
    return table[index].search(value); // Buscar en la lista correspondiente
}

template <typename DataType>
void ChainedHashTable<DataType>::remove(const DataType& value) {
    size_t index = value % size;
    DLListNode<DataType>* node = table[index].search(value);
    if (node != nullptr) {
        table[index].remove(node); // Eliminar el nodo si se encuentra
    }
}

template <typename DataType>
size_t ChainedHashTable<DataType>::getSize() const {
    return size;
}

template <typename DataType>
std::vector<DLList<DataType>> ChainedHashTable<DataType>::getTable() const {
    return table;
}

template <typename DataType>
void ChainedHashTable<DataType>::setTable(std::vector<DLList<DataType>> newTable) {
    table = newTable;
    size = table.size();
}