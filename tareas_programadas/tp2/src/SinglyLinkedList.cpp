#include "SinglyLinkedList.hpp"

// Implementation of SLListNode

// Default constructor: initializes key with default value and next as nullptr
template <typename DataType>
SLListNode<DataType>::SLListNode() : key(DataType()), next(nullptr) {}

// Constructor with given key and next pointer
template <typename DataType>
SLListNode<DataType>::SLListNode(const DataType& value, SLListNode<DataType>* next) 
    : key(value), next(next) {}

// Destructor
template <typename DataType>
SLListNode<DataType>::~SLListNode() {}

// Returns the key (data) stored in the node
template <typename DataType>
DataType SLListNode<DataType>::getKey() const {
    return key;
}

// Returns the pointer to the next node
template <typename DataType>
SLListNode<DataType>* SLListNode<DataType>::getNext() const {
    return next;
}

// Sets the key (data) of the node
template <typename DataType>
void SLListNode<DataType>::setKey(DataType key) {
    this->key = key;
}

// Sets the next pointer of the node
template <typename DataType>
void SLListNode<DataType>::setNext(SLListNode<DataType>* newNode) {
    next = newNode;
}

// Implementation of SLList

// Constructor: creates an empty list with sentinel node
template <typename DataType>
SLList<DataType>::SLList() {
    nil = new SLListNode<DataType>();
    nil->setNext(nil);  // sentinel node points to itself
}

// Destructor: deletes all nodes including sentinel
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

// Inserts a new node with the given value at the front of the list
template <typename DataType>
void SLList<DataType>::insert(const DataType& value) {
    SLListNode<DataType>* newNode = new SLListNode<DataType>(value, nil->getNext());
    nil->setNext(newNode);
}

// Searches for a node with the given value
template <typename DataType>
SLListNode<DataType>* SLList<DataType>::search(const DataType& value) const {
    SLListNode<DataType>* current = nil->getNext();
    while (current != nil && current->getKey() != value) {
        current = current->getNext();
    }
    return (current != nil) ? current : nullptr;
}

// Removes all nodes with the given value
template <typename DataType>
void SLList<DataType>::remove(const DataType& value) {
    SLListNode<DataType>* prev = nil;
    SLListNode<DataType>* current = nil->getNext();

    while (current != nil) {
        if (current->getKey() == value) {
            SLListNode<DataType>* toDelete = current;
            current = current->getNext();
            prev->setNext(current);
            delete toDelete;
        } else {
            prev = current;
            current = current->getNext();
        }
    }
}

// Returns the sentinel node
template <typename DataType>
SLListNode<DataType>* SLList<DataType>::getNil() const {
    return nil;
}

// Explicit instantiation of SLList for int type
template class SLList<int>;
