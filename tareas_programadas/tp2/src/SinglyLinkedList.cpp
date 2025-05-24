#include "SinglyLinkedList.hpp"

// Implementación de SLListNode

template <typename DataType>
SLListNode<DataType>::SLListNode() : key(DataType()), next(nullptr) {}

template <typename DataType>
SLListNode<DataType>::SLListNode(const DataType& value, SLListNode<DataType>* next) 
    : key(value), next(next) {}

template <typename DataType>
SLListNode<DataType>::~SLListNode() {}

template <typename DataType>
DataType SLListNode<DataType>::getKey() const {
    return key;
}

template <typename DataType>
SLListNode<DataType>* SLListNode<DataType>::getNext() const {
    return next;
}

template <typename DataType>
void SLListNode<DataType>::setKey(DataType key) {
    this->key = key;
}

template <typename DataType>
void SLListNode<DataType>::setNext(SLListNode<DataType>* newNode) {
    next = newNode;
}

// Implementación de SLList

// Implementar constructor por defecto
template <typename DataType>
SLList<DataType>::SLList() {
    nil = new SLListNode<DataType>();
    nil->setNext(nil);
}

// Implementar destructor
template <typename DataType>
SLList<DataType>::~SLList() {
    SLListNode<DataType>* current = nil->getNext();
    while (current != nil) {
        SLListNode<DataType>* temp = current;
        current = current->getNext();
        delete temp;
    }
    delete nil;
}

template <typename DataType>
void SLList<DataType>::insert(const DataType& value) {
    // Insertar al principio de la lista (después de nil)
    SLListNode<DataType>* newNode = new SLListNode<DataType>(value, nil->getNext());
    nil->setNext(newNode);
}

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::search(const DataType& value) const {
    SLListNode<DataType>* current = nil->getNext();
    while (current != nil && current->getKey() != value) {
        current = current->getNext();
    }
    return (current != nil) ? current : nullptr;
}

template <typename DataType>
void SLList<DataType>::remove(const DataType& value) {
    SLListNode<DataType>* prev = nil;
    SLListNode<DataType>* current = nil->getNext();
    
    while (current != nil && current->getKey() != value) {
        prev = current;
        current = current->getNext();
    }
    
    if (current != nil) { // Encontramos el nodo
        prev->setNext(current->getNext());
        delete current;
    }
}

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::getNil() const {
    return nil;
}

template class SLList<int>;
