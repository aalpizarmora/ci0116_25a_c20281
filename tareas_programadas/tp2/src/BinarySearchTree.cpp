/*
 Implementation of Binary Search Tree (BSTree) based on:
 Introduction to Algorithms, Third Edition - Cormen, Leiserson, Rivest, Stein
 Credits:
 - Initial design: Prof. Arturo Camacho, Universidad de Costa Rica
 - Modifications: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#include "BinarySearchTree.hpp"
#include <iostream>

// Implementation of BSTreeNode

template <typename DataType>
BSTreeNode<DataType>::BSTreeNode(const DataType &value, 
                               BSTreeNode<DataType> *parent,
                               BSTreeNode<DataType> *left,
                               BSTreeNode<DataType> *right)
    : key(value), parent(parent), left(left), right(right) {}

template <typename DataType>
BSTreeNode<DataType>::~BSTreeNode() {
    // Clean up left and right subtrees if they exist
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
}

template <typename DataType>
DataType BSTreeNode<DataType>::getKey() const {
    return key;
}

template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getParent() const {
    return parent;
}

template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getLeft() const {
    return left;
}

template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getRight() const {
    return right;
}

template <typename DataType>
void BSTreeNode<DataType>::setParent(BSTreeNode<DataType> *parent) {
    this->parent = parent;
}

template <typename DataType>
void BSTreeNode<DataType>::setLeft(BSTreeNode<DataType> *left) {
    this->left = left;
    if (left != nullptr) {
        left->setParent(this);
    }
}

template <typename DataType>
void BSTreeNode<DataType>::setRight(BSTreeNode<DataType> *right) {
    this->right = right;
    if (right != nullptr) {
        right->setParent(this);
    }
}

// Implementation of BSTree

template <typename DataType>
void BSTree<DataType>::insert(const DataType &value) {
    BSTreeNode<DataType> *newNode = new BSTreeNode<DataType>(value);
    BSTreeNode<DataType> *y = nullptr;
    BSTreeNode<DataType> *x = root;

    while (x != nullptr) {
        y = x;
        if (newNode->getKey() < x->getKey()) {
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }

    newNode->setParent(y);
    if (y == nullptr) {
        root = newNode;
    } else if (newNode->getKey() < y->getKey()) {
        y->setLeft(newNode);
    } else {
        y->setRight(newNode);
    }
}

template <typename DataType>
void BSTree<DataType>::remove(const DataType &value) {
    BSTreeNode<DataType> *node = search(root, value);
    if (node == nullptr) return;

    if (node->getLeft() == nullptr) {
        // Case 1: No left child
        BSTreeNode<DataType> *rightChild = node->getRight();
        if (node->getParent() == nullptr) {
            root = rightChild;
        } else if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeft(rightChild);
        } else {
            node->getParent()->setRight(rightChild);
        }
        if (rightChild != nullptr) {
            rightChild->setParent(node->getParent());
        }
        node->setLeft(nullptr);
        node->setRight(nullptr);
        delete node;
    } else if (node->getRight() == nullptr) {
        // Case 2: No right child
        BSTreeNode<DataType> *leftChild = node->getLeft();
        if (node->getParent() == nullptr) {
            root = leftChild;
        } else if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeft(leftChild);
        } else {
            node->getParent()->setRight(leftChild);
        }
        if (leftChild != nullptr) {
            leftChild->setParent(node->getParent());
        }
        node->setLeft(nullptr);
        node->setRight(nullptr);
        delete node;
    } else {
        // Case 3: Two children
        BSTreeNode<DataType> *successor = getSuccessor(node);
        DataType temp = successor->getKey();
        remove(temp);
        node->key = temp;
    }
}

template <typename DataType>
void BSTree<DataType>::inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree != nullptr) {
        inorderWalk(rootOfSubtree->getLeft());
        std::cout << rootOfSubtree->getKey() << " ";
        inorderWalk(rootOfSubtree->getRight());
    }
}

template <typename DataType>
void BSTree<DataType>::preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree != nullptr) {
        std::cout << rootOfSubtree->getKey() << " ";
        preorderWalk(rootOfSubtree->getLeft());
        preorderWalk(rootOfSubtree->getRight());
    }
}

template <typename DataType>
void BSTree<DataType>::postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree != nullptr) {
        postorderWalk(rootOfSubtree->getLeft());
        postorderWalk(rootOfSubtree->getRight());
        std::cout << rootOfSubtree->getKey() << " ";
    }
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::search(const BSTreeNode<DataType> *rootOfSubtree,
                                             const DataType &value) const {
    if (rootOfSubtree == nullptr || value == rootOfSubtree->getKey()) {
        return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
    }
    if (value < rootOfSubtree->getKey()) {
        return search(rootOfSubtree->getLeft(), value);
    } else {
        return search(rootOfSubtree->getRight(), value);
    }
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMinimum(
    const BSTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nullptr && rootOfSubtree->getLeft() != nullptr) {
        rootOfSubtree = rootOfSubtree->getLeft();
    }
    return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMaximum(
    const BSTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nullptr && rootOfSubtree->getRight() != nullptr) {
        rootOfSubtree = rootOfSubtree->getRight();
    }
    return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getSuccessor(
    const BSTreeNode<DataType> *node) const {
    if (node == nullptr) return nullptr;
    
    if (node->getRight() != nullptr) {
        return getMinimum(node->getRight());
    }
    
    BSTreeNode<DataType> *parent = node->getParent();
    BSTreeNode<DataType> *current = const_cast<BSTreeNode<DataType>*>(node);
    
    while (parent != nullptr && current == parent->getRight()) {
        current = parent;
        parent = parent->getParent();
    }
    
    return parent;
}

template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getRoot() const {
    return root;
}

template <typename DataType>
void BSTree<DataType>::fastInsert(size_t n) {
    // This is a placeholder for a more efficient insertion algorithm
    // In a real implementation, this might use a balanced insertion strategy
    // or bulk loading for better performance with large n
    for (size_t i = 0; i < n; ++i) {
        insert(DataType()); // Insert default-constructed values
    }
}