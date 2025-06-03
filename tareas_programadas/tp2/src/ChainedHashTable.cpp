#include "ChainedHashTable.hpp"

template <typename DataType>
ChainedHashTable<DataType>::ChainedHashTable(size_t size) : size(size) {
    // Resize the table vector to the given size
    table.resize(size);
}

template <typename DataType>
ChainedHashTable<DataType>::~ChainedHashTable() {
    // Lists are automatically destroyed because they are stored in a vector
}

template <typename DataType>
void ChainedHashTable<DataType>::insert(const DataType& value) {
    // Compute the index by taking modulo of the value
    size_t index = static_cast<size_t>(value) % size;
    // Insert value only if it is not already present in the bucket
    if (table[index].search(value) == nullptr) {
        table[index].insert(value);
    }
}

template <typename DataType>
DLListNode<DataType>* ChainedHashTable<DataType>::search(const DataType& value) const {
    // Compute the index for the value
    size_t index = static_cast<size_t>(value) % size;
    // Search for the value in the corresponding bucket
    return table[index].search(value);
}

template <typename DataType>
void ChainedHashTable<DataType>::remove(const DataType& value) {
    // Compute the index for the value
    size_t index = static_cast<size_t>(value) % size;
    DLListNode<DataType>* node;
    // Keep removing the value while it exists in the bucket
    while ((node = table[index].search(value)) != nullptr) {
        table[index].remove(value);
    }
}

template <typename DataType>
size_t ChainedHashTable<DataType>::getSize() const {
    // Return the size of the hash table (number of buckets)
    return size;
}

template <typename DataType>
std::vector<DLList<DataType>> ChainedHashTable<DataType>::getTable() const {
    // Return the vector of buckets (the hash table)
    return table;
}

template <typename DataType>
void ChainedHashTable<DataType>::setTable(std::vector<DLList<DataType>> newTable) {
    // Replace the current table with a new one and update size
    table = newTable;
    size = newTable.size();
}

// Explicit template instantiations for common types
template class ChainedHashTable<int>;
template class ChainedHashTable<float>;
template class ChainedHashTable<double>;