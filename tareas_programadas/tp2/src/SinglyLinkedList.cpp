#include "SinglyLinkedList.hpp"

// Implementation of SLListNode

template <typename DataType>
SLListNode<DataType>::SLListNode() : key(DataType()), next(nullptr) {}  
// Default constructor, empty key and next nullptr

template <typename DataType>
SLListNode<DataType>::SLListNode(const DataType& value, SLListNode<DataType>* next) 
    : key(value), next(next) {}  
    // Constructor with data and next node pointer

template <typename DataType>
SLListNode<DataType>::~SLListNode() {} 
    // Destructor

template <typename DataType>
DataType SLListNode<DataType>::getKey() const {
    return key;
    // Returns the stored data
}

template <typename DataType>
SLListNode<DataType>* SLListNode<DataType>::getNext() const {
    return next;
    // Returns the pointer to next node
}

template <typename DataType>
void SLListNode<DataType>::setKey(DataType key) {
    this->key = key;
    // Sets the stored data
}

template <typename DataType>
void SLListNode<DataType>::setNext(SLListNode<DataType>* newNode) {
    next = newNode;
    // Sets the pointer to the next node
}

// Implementation of SLList

template <typename DataType>
SLList<DataType>::SLList() {
    nil = new SLListNode<DataType>();
    // Create sentinel node
    nil->setNext(nil);
    // nil points to itself (empty list)
}

template <typename DataType>
SLList<DataType>::~SLList() {
    SLListNode<DataType>* current = nil->getNext();
    // Traverse and delete all nodes except nil
    while (current != nil) {
        SLListNode<DataType>* temp = current;
        current = current->getNext();
        delete temp;
    }
    delete nil;
    // Delete sentinel node
}

template <typename DataType>
void SLList<DataType>::insert(const DataType& value) {
    // Insert new node right after nil (at the front)
    SLListNode<DataType>* newNode = new SLListNode<DataType>(value, nil->getNext());
    nil->setNext(newNode);
}

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::search(const DataType& value) const {
    SLListNode<DataType>* current = nil->getNext();
    // Search for node with given value
    while (current != nil && current->getKey() != value) {
        current = current->getNext();
    }
    return (current != nil) ? current : nullptr;
    // Return node or nullptr if not found
}

template <typename DataType>
void SLList<DataType>::remove(const DataType& value) {
    SLListNode<DataType>* prev = nil;
    SLListNode<DataType>* current = nil->getNext();
    
    // Find node to remove and its previous node
    while (current != nil && current->getKey() != value) {
        prev = current;
        current = current->getNext();
    }
    
    if (current != nil) {
        // If found the node
        prev->setNext(current->getNext());
        // Bypass the node
        delete current;
        // Free memory
    }
}

template <typename DataType>
SLListNode<DataType>* SLList<DataType>::getNil() const {
    return nil;
    // Return the sentinel node
}

template class SLList<int>;
// Explicit instantiation for int