#include "DoublyLinkedList.hpp"

// Implementation of DLListNode

template <typename DataType>
DLListNode<DataType>::DLListNode(const DataType& value, 
                                DLListNode<DataType>* next,
                                DLListNode<DataType>* prev) 
    : key(value), next(next), prev(prev) {}

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

// Implementation of DLList

template <typename DataType>
void DLList<DataType>::insert(const DataType& value) {
    // Insert at the beginning of the list (after nil)
    DLListNode<DataType>* newNode = new DLListNode<DataType>(value, nil->getNext(), nil);
    nil->getNext()->setPrev(newNode);
    nil->setNext(newNode);
}

template <typename DataType>
DLListNode<DataType>* DLList<DataType>::search(const DataType& value) const {
    DLListNode<DataType>* current = nil->getNext();
    while (current != nil && current->getKey() != value) {
        current = current->getNext();
    }
    return (current != nil) ? current : nullptr;
}

template <typename DataType>
void DLList<DataType>::remove(const DataType& value) {
    DLListNode<DataType>* node = search(value);
    if (node != nullptr) {
        remove(node);
    }
}

template <typename DataType>
void DLList<DataType>::remove(DLListNode<DataType>* node) {
    if (node == nullptr || node == nil) return;
    
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    delete node;
}

template <typename DataType>
DLListNode<DataType>* DLList<DataType>::getNil() const {
    return nil;
}