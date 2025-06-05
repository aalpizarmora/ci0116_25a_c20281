#include "ChainedHashTable.hpp"

template <typename DataType>
ChainedHashTable<DataType>::ChainedHashTable(size_t size) : size(size) {
    table.resize(size);
}

template <typename DataType>
ChainedHashTable<DataType>::~ChainedHashTable() {
    // Las listas se destruyen automáticamente porque están en un vector
}

template <typename DataType>
void ChainedHashTable<DataType>::insert(const DataType& value) {
    size_t index = static_cast<size_t>(value) % size;
    if (table[index].search(value) == nullptr) {
        table[index].insert(value);
    }
}

template <typename DataType>
DLListNode<DataType>* ChainedHashTable<DataType>::search(const DataType& value) const {
    size_t index = static_cast<size_t>(value) % size;
    return table[index].search(value);
}

template <typename DataType>
void ChainedHashTable<DataType>::remove(const DataType& value) {
    size_t index = static_cast<size_t>(value) % size;
    DLListNode<DataType>* node;
    while ((node = table[index].search(value)) != nullptr) {
        table[index].remove(value);
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
    size = newTable.size();
}

// Instanciaciones explícitas comunes
template class ChainedHashTable<int>;
template class ChainedHashTable<float>;
template class ChainedHashTable<double>;
