#include "RedBlackTree.hpp"
#include <iostream>

// Implementation of RBTreeNode

template <typename DataType>
RBTreeNode<DataType>::RBTreeNode(const DataType &value, 
                               RBTreeNode<DataType> *parent,
                               RBTreeNode<DataType> *left,
                               RBTreeNode<DataType> *right, 
                               enum colors c)
    : key(value), parent(parent), left(left), right(right), color(c) {}

template <typename DataType>
RBTreeNode<DataType>::~RBTreeNode() {
    // Clean up left and right subtrees if they exist
    if (left != nullptr && left != this) delete left;
    if (right != nullptr && right != this) delete right;
}

template <typename DataType>
DataType RBTreeNode<DataType>::getKey() const {
    return key;
}

template <typename DataType>
RBTreeNode<DataType>* RBTreeNode<DataType>::getParent() const {
    return parent;
}

template <typename DataType>
RBTreeNode<DataType>* RBTreeNode<DataType>::getLeft() const {
    return left;
}

template <typename DataType>
RBTreeNode<DataType>* RBTreeNode<DataType>::getRight() const {
    return right;
}

template <typename DataType>
void RBTreeNode<DataType>::setKey(DataType key) {
    this->key = key;
}

template <typename DataType>
void RBTreeNode<DataType>::setParent(RBTreeNode<DataType> *parent) {
    this->parent = parent;
}

template <typename DataType>
void RBTreeNode<DataType>::setLeft(RBTreeNode<DataType> *left) {
    this->left = left;
    if (left != nullptr) {
        left->setParent(this);
    }
}

template <typename DataType>
void RBTreeNode<DataType>::setRight(RBTreeNode<DataType> *right) {
    this->right = right;
    if (right != nullptr) {
        right->setParent(this);
    }
}

// Implementation of RBTree

template <typename DataType>
RBTree<DataType>::RBTree() {
    nil = new RBTreeNode<DataType>();
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nil;
    root = nil;
}

template <typename DataType>
RBTree<DataType>::~RBTree() {
    if (root != nil) delete root;
    delete nil;
}

template <typename DataType>
void RBTree<DataType>::insert(const DataType &value) {
    RBTreeNode<DataType> *z = new RBTreeNode<DataType>(value, nil, nil, nil, RED);
    RBTreeNode<DataType> *y = nil;
    RBTreeNode<DataType> *x = root;

    while (x != nil) {
        y = x;
        if (z->getKey() < x->getKey()) {
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }

    z->setParent(y);
    if (y == nil) {
        root = z;
    } else if (z->getKey() < y->getKey()) {
        y->setLeft(z);
    } else {
        y->setRight(z);
    }

    z->setLeft(nil);
    z->setRight(nil);
    z->color = RED;
    insertFixup(z);
}

template <typename DataType>
void RBTree<DataType>::insertFixup(RBTreeNode<DataType> *z) {
    while (z->getParent()->color == RED) {
        if (z->getParent() == z->getParent()->getParent()->getLeft()) {
            RBTreeNode<DataType> *y = z->getParent()->getParent()->getRight();
            if (y->color == RED) {
                z->getParent()->color = BLACK;
                y->color = BLACK;
                z->getParent()->getParent()->color = RED;
                z = z->getParent()->getParent();
            } else {
                if (z == z->getParent()->getRight()) {
                    z = z->getParent();
                    leftRotate(z);
                }
                z->getParent()->color = BLACK;
                z->getParent()->getParent()->color = RED;
                rightRotate(z->getParent()->getParent());
            }
        } else {
            RBTreeNode<DataType> *y = z->getParent()->getParent()->getLeft();
            if (y->color == RED) {
                z->getParent()->color = BLACK;
                y->color = BLACK;
                z->getParent()->getParent()->color = RED;
                z = z->getParent()->getParent();
            } else {
                if (z == z->getParent()->getLeft()) {
                    z = z->getParent();
                    rightRotate(z);
                }
                z->getParent()->color = BLACK;
                z->getParent()->getParent()->color = RED;
                leftRotate(z->getParent()->getParent());
            }
        }
    }
    root->color = BLACK;
}

template <typename DataType>
void RBTree<DataType>::leftRotate(RBTreeNode<DataType> *x) {
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
    RBTreeNode<DataType> *z = search(root, value);
    if (z == nil) return;

    RBTreeNode<DataType> *y = z;
    RBTreeNode<DataType> *x;
    enum colors yOriginalColor = y->color;

    if (z->getLeft() == nil) {
        x = z->getRight();
        transplant(z, z->getRight());
    } else if (z->getRight() == nil) {
        x = z->getLeft();
        transplant(z, z->getLeft());
    } else {
        y = getMinimum(z->getRight());
        yOriginalColor = y->color;
        x = y->getRight();
        if (y->getParent() == z) {
            x->setParent(y);
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

    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
    delete z;
}

template <typename DataType>
void RBTree<DataType>::transplant(RBTreeNode<DataType> *u, RBTreeNode<DataType> *v) {
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
    while (x != root && x->color == BLACK) {
        if (x == x->getParent()->getLeft()) {
            RBTreeNode<DataType> *w = x->getParent()->getRight();
            if (w->color == RED) {
                w->color = BLACK;
                x->getParent()->color = RED;
                leftRotate(x->getParent());
                w = x->getParent()->getRight();
            }
            if (w->getLeft()->color == BLACK && w->getRight()->color == BLACK) {
                w->color = RED;
                x = x->getParent();
            } else {
                if (w->getRight()->color == BLACK) {
                    w->getLeft()->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->getParent()->getRight();
                }
                w->color = x->getParent()->color;
                x->getParent()->color = BLACK;
                w->getRight()->color = BLACK;
                leftRotate(x->getParent());
                x = root;
            }
        } else {
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
    if (rootOfSubtree == nil || value == rootOfSubtree->getKey()) {
        return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    }
    if (value < rootOfSubtree->getKey()) {
        return search(rootOfSubtree->getLeft(), value);
    } else {
        return search(rootOfSubtree->getRight(), value);
    }
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getMinimum(
    const RBTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nil && rootOfSubtree->getLeft() != nil) {
        rootOfSubtree = rootOfSubtree->getLeft();
    }
    return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getMaximum(
    const RBTreeNode<DataType> *rootOfSubtree) const {
    while (rootOfSubtree != nil && rootOfSubtree->getRight() != nil) {
        rootOfSubtree = rootOfSubtree->getRight();
    }
    return const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getSuccessor(
    const RBTreeNode<DataType> *node) const {
    if (node == nil) return nil;
    
    if (node->getRight() != nil) {
        return getMinimum(node->getRight());
    }
    
    RBTreeNode<DataType> *parent = node->getParent();
    RBTreeNode<DataType> *current = const_cast<RBTreeNode<DataType>*>(node);
    
    while (parent != nil && current == parent->getRight()) {
        current = parent;
        parent = parent->getParent();
    }
    
    return parent;
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getRoot() const {
    return root;
}

template <typename DataType>
RBTreeNode<DataType>* RBTree<DataType>::getNil() const {
    return nil;
}