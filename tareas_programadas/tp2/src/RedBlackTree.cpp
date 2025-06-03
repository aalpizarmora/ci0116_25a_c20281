#include "RedBlackTree.hpp"
#include <iostream>

// Implementation of RBTreeNode

// Default constructor: initializes with default values and color BLACK
template <typename DataType>
RBTreeNode<DataType>::RBTreeNode()
    : key(), parent(nullptr), left(nullptr), right(nullptr), color(BLACK) {}

// Parameterized constructor: initializes node with provided values
template <typename DataType>
RBTreeNode<DataType>::RBTreeNode(const DataType &value, 
                               RBTreeNode<DataType> *parent,
                               RBTreeNode<DataType> *left,
                               RBTreeNode<DataType> *right, 
                               enum colors c)
    : key(value), parent(parent), left(left), right(right), color(c) {}

// Destructor: nothing special needed
template <typename DataType>
RBTreeNode<DataType>::~RBTreeNode() {}

// Returns the key of the node
template <typename DataType>
DataType RBTreeNode<DataType>::getKey() const {
    return key;
}

// Returns the parent node
template <typename DataType>
RBTreeNode<DataType>* RBTreeNode<DataType>::getParent() const {
    return parent;
}

// Returns the left child
template <typename DataType>
RBTreeNode<DataType>* RBTreeNode<DataType>::getLeft() const {
    return left;
}

// Returns the right child
template <typename DataType>
RBTreeNode<DataType>* RBTreeNode<DataType>::getRight() const {
    return right;
}

// Sets the key of the node
template <typename DataType>
void RBTreeNode<DataType>::setKey(DataType key) {
    this->key = key;
}

// Sets the parent of the node
template <typename DataType>
void RBTreeNode<DataType>::setParent(RBTreeNode<DataType> *parent) {
    this->parent = parent;
}

// Sets the left child and updates its parent
template <typename DataType>
void RBTreeNode<DataType>::setLeft(RBTreeNode<DataType> *left) {
    this->left = left;
    if (left != nullptr) {
        left->setParent(this);
    }
}

// Sets the right child and updates its parent
template <typename DataType>
void RBTreeNode<DataType>::setRight(RBTreeNode<DataType> *right) {
    this->right = right;
    if (right != nullptr) {
        right->setParent(this);
    }
}

// Implementation of RBTree

// Constructor: creates the sentinel nil node and sets root to nil
template <typename DataType>
RBTree<DataType>::RBTree() {
    nil = new RBTreeNode<DataType>();
    nil->color = BLACK;
    nil->setLeft(nil);
    nil->setRight(nil);
    nil->setParent(nil);
    nil->key = DataType();  // default value
    root = nil;
}

// Destructor: clears the tree and deletes the nil node
template <typename DataType>
RBTree<DataType>::~RBTree() {
    clear(root);
    delete nil;
}

// Recursively deletes nodes in post-order
template <typename DataType>
void RBTree<DataType>::clear(RBTreeNode<DataType>* node) {
    if (node == nil) return;
    clear(node->getLeft());
    clear(node->getRight());
    delete node;
}

// Inserts a new node with the given value into the tree
template <typename DataType>
void RBTree<DataType>::insert(const DataType &value) {
    // Create a new node with color RED
    RBTreeNode<DataType> *z = new RBTreeNode<DataType>(value, nil, nil, nil, RED);
    RBTreeNode<DataType> *y = nil;
    RBTreeNode<DataType> *x = root;

    // Find the correct position for the new node
    while (x != nil) {
        y = x;
        if (z->getKey() < x->getKey()) {
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }

    // Set the parent of the new node
    z->setParent(y);
    if (y == nil) {
        root = z;  // Tree was empty
    } else if (z->getKey() < y->getKey()) {
        y->setLeft(z);
    } else {
        y->setRight(z);
    }

    // Set children and fix color
    z->setLeft(nil);
    z->setRight(nil);
    z->color = RED;

    // Fix any violations of the Red-Black Tree properties
    insertFixup(z);
}

template <typename DataType>
void RBTree<DataType>::insertFixup(RBTreeNode<DataType> *z) {
    // Fix the Red-Black properties after insertion
    while (z->getParent()->color == RED) {
        if (z->getParent() == z->getParent()->getParent()->getLeft()) {
            RBTreeNode<DataType> *y = z->getParent()->getParent()->getRight(); // uncle
            if (y->color == RED) {
                // Case 1: Uncle is red - recolor
                z->getParent()->color = BLACK;
                y->color = BLACK;
                z->getParent()->getParent()->color = RED;
                z = z->getParent()->getParent();
            } else {
                if (z == z->getParent()->getRight()) {
                    // Case 2: Triangle case - rotate left
                    z = z->getParent();
                    leftRotate(z);
                }
                // Case 3: Line case - rotate right
                z->getParent()->color = BLACK;
                z->getParent()->getParent()->color = RED;
                rightRotate(z->getParent()->getParent());
            }
        } else {
            // Same as above, but mirrored
            RBTreeNode<DataType> *y = z->getParent()->getParent()->getLeft(); // uncle
            if (y->color == RED) {
                // Case 1: Uncle is red - recolor
                z->getParent()->color = BLACK;
                y->color = BLACK;
                z->getParent()->getParent()->color = RED;
                z = z->getParent()->getParent();
            } else {
                if (z == z->getParent()->getLeft()) {
                    // Case 2: Triangle case - rotate right
                    z = z->getParent();
                    rightRotate(z);
                }
                // Case 3: Line case - rotate left
                z->getParent()->color = BLACK;
                z->getParent()->getParent()->color = RED;
                leftRotate(z->getParent()->getParent());
            }
        }
    }
    // Always make sure the root is black
    root->color = BLACK;
}

template <typename DataType>
void RBTree<DataType>::leftRotate(RBTreeNode<DataType> *x) {
    // Left rotate around node x
    RBTreeNode<DataType> *y = x->getRight();
    x->setRight(y->getLeft());
    if (y->getLeft() != nil) {
        y->getLeft()->setParent(x);
    }
    y->setParent(x->getParent());
    if (x->getParent() == nil) {
        root = y;
    } else if (x == x->getParent()->getLeft()) {
        x->getParent()->setLeft(y);
    } else {
        x->getParent()->setRight(y);
    }
    y->setLeft(x);
    x->setParent(y);
}

template <typename DataType>
void RBTree<DataType>::rightRotate(RBTreeNode<DataType> *y) {
    // Right rotate around node y
    RBTreeNode<DataType> *x = y->getLeft();
    y->setLeft(x->getRight());
    if (x->getRight() != nil) {
        x->getRight()->setParent(y);
    }
    x->setParent(y->getParent());
    if (y->getParent() == nil) {
        root = x;
    } else if (y == y->getParent()->getRight()) {
        y->getParent()->setRight(x);
    } else {
        y->getParent()->setLeft(x);
    }
    x->setRight(y);
    y->setParent(x);
}

template <typename DataType>
void RBTree<DataType>::remove(const DataType &value) {
    // Search the node to remove
    RBTreeNode<DataType>* z = search(root, value);
    if (z == nil) return;

    RBTreeNode<DataType>* y = z;
    RBTreeNode<DataType>* x;
    enum colors yOriginalColor = y->color;

    if (z->getLeft() == nil) {
        // Case: No left child
        x = z->getRight();
        transplant(z, z->getRight());
    } else if (z->getRight() == nil) {
        // Case: No right child
        x = z->getLeft();
        transplant(z, z->getLeft());
    } else {
        // Case: Two children
        y = getMinimum(z->getRight()); // Find successor
        yOriginalColor = y->color;
        x = y->getRight();

        if (y->getParent() == z) {
            x->setParent(y); // Even if x == nil
        } else {
            transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }

        transplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
        y->color = z->color;
    }

    // If a black node was removed, fix violations
    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
}

template <typename DataType>
void RBTree<DataType>::transplant(RBTreeNode<DataType> *u, RBTreeNode<DataType> *v) {
    // Replace subtree u with subtree v
    if (u->getParent() == nil) {
        root = v;
    } else if (u == u->getParent()->getLeft()) {
        u->getParent()->setLeft(v);
    } else {
        u->getParent()->setRight(v);
    }
    v->setParent(u->getParent());
}

template <typename DataType>
void RBTree<DataType>::deleteFixup(RBTreeNode<DataType> *x) {
    // Fix the Red-Black properties after deletion
    while (x != root && x->color == BLACK) {
        if (x == x->getParent()->getLeft()) {
            RBTreeNode<DataType> *w = x->getParent()->getRight();
            if (w->color == RED) {
                // Case 1: Sibling is red
                w->color = BLACK;
                x->getParent()->color = RED;
                leftRotate(x->getParent());
                w = x->getParent()->getRight();
            }
            if (w->getLeft()->color == BLACK && w->getRight()->color == BLACK) {
                // Case 2: Sibling's children are black
                w->color = RED;
                x = x->getParent();
            } else {
                if (w->getRight()->color == BLACK) {
                    // Case 3: Sibling's right is black
                    w->getLeft()->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->getParent()->getRight();
                }
                // Case 4: Sibling's right is red
                w->color = x->getParent()->color;
                x->getParent()->color = BLACK;
                w->getRight()->color = BLACK;
                leftRotate(x->getParent());
                x = root;
            }
        } else {
            // Same as above, but mirrored
            RBTreeNode<DataType> *w = x->getParent()->getLeft();
            if (w->color == RED) {
                w->color = BLACK;
                x->getParent()->color = RED;
                rightRotate(x->getParent());
                w = x->getParent()->getLeft();
            }
            if (w->getRight()->color == BLACK && w->getLeft()->color == BLACK) {
                w->color = RED;
                x = x->getParent();
            } else {
                if (w->getLeft()->color == BLACK) {
                    w->getRight()->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->getParent()->getLeft();
                }
                w->color = x->getParent()->color;
                x->getParent()->color = BLACK;
                w->getLeft()->color = BLACK;
                rightRotate(x->getParent());
                x = root;
            }
        }
    }
    x->color = BLACK;
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::search(const RBTreeNode<DataType> *rootOfSubtree,
                                               const DataType &value) const {
    RBTreeNode<DataType>* current = const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    while (current != nil && current->getKey() != value) {
        if (value < current->getKey()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    return current;
}

// Returns the node with the minimum key in the given subtree
template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getMinimum(
    const RBTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nil && rootOfSubtree->getLeft() != nil) {
        rootOfSubtree = rootOfSubtree->getLeft(); // Go as left as possible
    }
    return const_cast<RBTreeNode<DataType>*>(rootOfSubtree); // Remove const for return
}

// Returns the node with the maximum key in the given subtree
template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getMaximum(
    const RBTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nil && rootOfSubtree->getRight() != nil) {
        rootOfSubtree = rootOfSubtree->getRight(); // Go as right as possible
    }
    return const_cast<RBTreeNode<DataType>*>(rootOfSubtree); // Remove const for return
}

// Returns the in-order successor of the given node
template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getSuccessor(
    const RBTreeNode<DataType> *node) const {
    if (node == nil) return nil; // No successor for nil node
    
    if (node->getRight() != nil) {
        return getMinimum(node->getRight()); // Successor is min in right subtree
    }
    
    RBTreeNode<DataType> *parent = node->getParent();
    RBTreeNode<DataType> *current = const_cast<RBTreeNode<DataType>*>(node);
    
    // Go up until we find a parent where current is a left child
    while (parent != nil && current == parent->getRight()) {
        current = parent;
        parent = parent->getParent();
    }
    
    return parent; // This parent is the successor
}

// Returns the root of the red-black tree
template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getRoot() const {
    return root;
}

// Returns the sentinel nil node
template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getNil() const {
    return nil;
}

// Explicit instantiation of RBTree with int type
template class RBTree<int>;
