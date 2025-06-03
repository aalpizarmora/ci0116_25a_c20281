#include "BinarySearchTree.hpp"
#include <iostream>

// Implementation of BSTreeNode

// Default constructor
template <typename DataType>
BSTreeNode<DataType>::BSTreeNode() : key(), parent(nullptr), left(nullptr), right(nullptr) {}

// Parameterized constructor
template <typename DataType>
BSTreeNode<DataType>::BSTreeNode(const DataType &value, 
                               BSTreeNode<DataType> *parent,
                               BSTreeNode<DataType> *left,
                               BSTreeNode<DataType> *right)
    : key(value), parent(parent), left(left), right(right) {}

// Destructor - deletes left and right subtrees recursively
template <typename DataType>
BSTreeNode<DataType>::~BSTreeNode() {
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
}

// Returns the value of the node
template <typename DataType>
DataType BSTreeNode<DataType>::getKey() const {
    return key;
}

// Returns the parent of the node
template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getParent() const {
    return parent;
}

// Returns the left child
template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getLeft() const {
    return left;
}

// Returns the right child
template <typename DataType>
BSTreeNode<DataType>* BSTreeNode<DataType>::getRight() const {
    return right;
}

// Sets the parent of the node
template <typename DataType>
void BSTreeNode<DataType>::setParent(BSTreeNode<DataType> *parent) {
    this->parent = parent;
}

// Sets the left child and updates its parent
template <typename DataType>
void BSTreeNode<DataType>::setLeft(BSTreeNode<DataType> *left) {
    this->left = left;
    if (left != nullptr) {
        left->setParent(this);
    }
}

// Sets the right child and updates its parent
template <typename DataType>
void BSTreeNode<DataType>::setRight(BSTreeNode<DataType> *right) {
    this->right = right;
    if (right != nullptr) {
        right->setParent(this);
    }
}

// Implementation of BSTree

// Default constructor
template <typename DataType>
BSTree<DataType>::BSTree() : root(nullptr) {}

// Destructor - deletes the entire tree
template <typename DataType>
BSTree<DataType>::~BSTree() {
    if (root != nullptr) delete root;
}

// Inserts a value into the tree
template <typename DataType>
void BSTree<DataType>::insert(const DataType &value) {
    BSTreeNode<DataType> *newNode = new BSTreeNode<DataType>(value);
    BSTreeNode<DataType> *y = nullptr;
    BSTreeNode<DataType> *x = root;

    // Find the correct position for the new node
    while (x != nullptr) {
        y = x;
        if (newNode->getKey() < x->getKey()) {
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }

    // Set the parent of the new node
    newNode->setParent(y);
    
    // Insert as root or as left/right child
    if (y == nullptr) {
        root = newNode;
    } else if (newNode->getKey() < y->getKey()) {
        y->setLeft(newNode);
    } else {
        y->setRight(newNode);
    }
}

// Private helper method to replace one subtree with another
template <typename DataType>
void BSTree<DataType>::transplant(BSTreeNode<DataType> *u, BSTreeNode<DataType> *v) {
    if (u->getParent() == nullptr) {
        // If u is root, set v as new root
        root = v;
    } else if (u == u->getParent()->getLeft()) {
        // If u is left child, set v as left child
        u->getParent()->setLeft(v);
    } else {
        // If u is right child, set v as right child
        u->getParent()->setRight(v);
    }
    if (v != nullptr) {
        // Update parent of v
        v->setParent(u->getParent());
    }
}

// Remove a node with given value from the tree
template <typename DataType>
void BSTree<DataType>::remove(const DataType &value) {
    BSTreeNode<DataType> *z = search(root, value);
    if (z == nullptr) return; // Node not found

    if (z->getLeft() == nullptr) {
        // Node has no left child
        transplant(z, z->getRight());
    } else if (z->getRight() == nullptr) {
        // Node has no right child
        transplant(z, z->getLeft());
    } else {
        // Node has two children
        BSTreeNode<DataType> *y = getMinimum(z->getRight()); // Successor
        if (y->getParent() != z) {
            // Move y up
            transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }
        transplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
    }
    // Disconnect and delete node
    z->setLeft(nullptr);
    z->setRight(nullptr);
    delete z;
}

// In-order traversal: left, root, right
#include <stack>

template <typename DataType>
void BSTree<DataType>::inorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    std::stack<BSTreeNode<DataType>*> stack;
    BSTreeNode<DataType>* current = rootOfSubtree;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->getLeft();
        }

        current = stack.top();
        stack.pop();

        std::cout << current->getKey() << " ";

        current = current->getRight();
    }
}

// Pre-order traversal: root, left, right
template <typename DataType>
void BSTree<DataType>::preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree != nullptr) {
        std::cout << rootOfSubtree->getKey() << " ";
        preorderWalk(rootOfSubtree->getLeft());
        preorderWalk(rootOfSubtree->getRight());
    }
}

// Post-order traversal: left, right, root
template <typename DataType>
void BSTree<DataType>::postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    if (rootOfSubtree != nullptr) {
        postorderWalk(rootOfSubtree->getLeft());
        postorderWalk(rootOfSubtree->getRight());
        std::cout << rootOfSubtree->getKey() << " ";
    }
}

// Iterative search for a value starting from a subtree root
template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::search(const BSTreeNode<DataType>* rootOfSubtree, const DataType& value) const {
    BSTreeNode<DataType>* current = const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
    while (current != nullptr && current->getKey() != value) {
        if (value < current->getKey()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    return current;
}

// Get node with minimum key in a subtree
template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMinimum(
    const BSTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nullptr && rootOfSubtree->getLeft() != nullptr) {
        rootOfSubtree = rootOfSubtree->getLeft();
    }
    return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
}

// Get node with maximum key in a subtree
template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getMaximum(
    const BSTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nullptr && rootOfSubtree->getRight() != nullptr) {
        rootOfSubtree = rootOfSubtree->getRight();
    }
    return const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
}

// Get successor of a given node in the tree
template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getSuccessor(
    const BSTreeNode<DataType> *node) const {
    if (node == nullptr) return nullptr;
    
    if (node->getRight() != nullptr) {
        // Successor is minimum in right subtree
        return getMinimum(node->getRight());
    }
    
    // Go up until we find a node that is left child of its parent
    BSTreeNode<DataType> *parent = node->getParent();
    BSTreeNode<DataType> *current = const_cast<BSTreeNode<DataType>*>(node);
    
    while (parent != nullptr && current == parent->getRight()) {
        current = parent;
        parent = parent->getParent();
    }
    
    return parent;
}

// Return the root of the tree
template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::getRoot() const {
    return root;
}

// Build a balanced BST from range [start, end]
template <typename DataType>
BSTreeNode<DataType>* BSTree<DataType>::buildBalancedSubtree(DataType start, DataType end, BSTreeNode<DataType>* parent) {
    if (start > end) return nullptr;
    
    DataType mid = start + (end - start) / 2;
    BSTreeNode<DataType>* newNode = new BSTreeNode<DataType>(mid, parent);
    
    newNode->left = buildBalancedSubtree(start, mid - 1, newNode);
    newNode->right = buildBalancedSubtree(mid + 1, end, newNode);
    
    return newNode;
}

// Insert n sequential values [0, n-1] into a balanced BST
template <typename DataType>
void BSTree<DataType>::fastInsert(size_t n) {
    delete root;
    root = nullptr;
    if (n > 0) {
        root = buildBalancedSubtree(static_cast<DataType>(0), 
                                  static_cast<DataType>(n - 1), 
                                  nullptr);
    }
}

// Explicit instantiations of BSTree for common types
template class BSTree<int>;
template class BSTree<float>;
template class BSTree<double>;
