#include "DoublyLinkedList.hpp"
#include <iostream>  // Optional, in case you want to print for testing

// Node constructor
template <typename DataType>
DLListNode<DataType>::DLListNode(const DataType& value, DLListNode<DataType>* next, DLListNode<DataType>* prev)
    : key(value), next(next), prev(prev) {}

// Node methods
template <typename DataType>
DataType DLListNode<DataType>::getKey() const {
    return key;
}

template <typename DataType>
DLListNode<DataType>* DLListNode<DataType>::getPrev() const {
    return prev;
}

template <typename DataType>
DLListNode<DataType>* DLListNode<DataType>::getNext() const {
    return next;
}

template <typename DataType>
void DLListNode<DataType>::setKey(DataType key) {
    this->key = key;
}

template <typename DataType>
void DLListNode<DataType>::setPrev(DLListNode<DataType>* prev) {
    this->prev = prev;
}

template <typename DataType>
void DLListNode<DataType>::setNext(DLListNode<DataType>* next) {
    this->next = next;
}

// List constructor
template <typename DataType>
DLList<DataType>::DLList() {
    // Initialize the sentinel node
    nil = new DLListNode<DataType>();
    nil->next = nil;
    nil->prev = nil;
}

// List destructor
template <typename DataType>
DLList<DataType>::~DLList() {
    DLListNode<DataType>* current = nil->next;
    while (current != nil) {
        DLListNode<DataType>* next = current->next;
        delete current;
        current = next;
    }
    delete nil;
}

// Insert at the beginning (after the sentinel)
template <typename DataType>
void DLList<DataType>::insert(const DataType& value) {
    DLListNode<DataType>* newNode = new DLListNode<DataType>(value, nil->next, nil);
    nil->next->prev = newNode;
    nil->next = newNode;
}

// Search for a node with the given value
template <typename DataType>
DLListNode<DataType>* DLList<DataType>::search(const DataType& value) const {
    DLListNode<DataType>* current = nil->next;
    while (current != nil && current->key != value) {
        current = current->next;
    }
    return (current == nil) ? nullptr : current;
}

// Remove a node with a specific value
template <typename DataType>
void DLList<DataType>::remove(const DataType& value) {
    DLListNode<DataType>* current = nil->next;

    while (current != nil) {
        DLListNode<DataType>* next = current->next;
        if (current->key == value) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        current = next;
    }
}

// Remove the given node (assumes it's valid and not nullptr)
template <typename DataType>
void DLList<DataType>::remove(DLListNode<DataType>* node) {
    if (node == nullptr || node == nil) return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

// Return the sentinel node
template <typename DataType>
DLListNode<DataType>* DLList<DataType>::getNil() const {
    return nil;
}

// Explicit instantiations for types used in your project
template class DLListNode<int>;
template class DLListNode<float>;
template class DLListNode<double>;

template class DLList<int>;
template class DLList<float>;
template class DLList<double>;
