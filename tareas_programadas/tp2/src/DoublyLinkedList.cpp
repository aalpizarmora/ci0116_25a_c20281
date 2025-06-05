#include "DoublyLinkedList.hpp"
#include <iostream>  // Opcional, por si quieres imprimir para pruebas

// Constructor del nodo
template <typename DataType>
DLListNode<DataType>::DLListNode(const DataType& value, DLListNode<DataType>* next, DLListNode<DataType>* prev)
    : key(value), next(next), prev(prev) {}

// Métodos del nodo
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

// Constructor de la lista
template <typename DataType>
DLList<DataType>::DLList() {
    // Inicializa el nodo sentinela
    nil = new DLListNode<DataType>();
    nil->next = nil;
    nil->prev = nil;
}

// Destructor de la lista
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

// Inserta al inicio (después del sentinela)
template <typename DataType>
void DLList<DataType>::insert(const DataType& value) {
    DLListNode<DataType>* newNode = new DLListNode<DataType>(value, nil->next, nil);
    nil->next->prev = newNode;
    nil->next = newNode;
}

// Busca un nodo con el valor dado
template <typename DataType>
DLListNode<DataType>* DLList<DataType>::search(const DataType& value) const {
    DLListNode<DataType>* current = nil->next;
    while (current != nil && current->key != value) {
        current = current->next;
    }
    return (current == nil) ? nullptr : current;
}

// Elimina un nodo con un valor específico
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

// Elimina el nodo dado (asume que es válido y no nullptr)
template <typename DataType>
void DLList<DataType>::remove(DLListNode<DataType>* node) {
    if (node == nullptr || node == nil) return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

// Devuelve el nodo sentinela
template <typename DataType>
DLListNode<DataType>* DLList<DataType>::getNil() const {
    return nil;
}

// Instanciaciones explícitas para tipos usados en tu proyecto
template class DLListNode<int>;
template class DLListNode<float>;
template class DLListNode<double>;

template class DLList<int>;
template class DLList<float>;
template class DLList<double>;

