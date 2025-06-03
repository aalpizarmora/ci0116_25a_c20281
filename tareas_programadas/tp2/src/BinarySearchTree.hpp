/*
 * @file BSTree.hpp
 * @brief Binary Search Tree (BST) declarations.
 * @authors
 *   Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 *   Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstddef>

/// @brief Forward declaration of BSTree.
template <typename DataType>
class BSTree;

/**
 * @class BSTreeNode
 * @brief Node class for a Binary Search Tree.
 * @tparam DataType The type of the data stored in the node.
 */
template <typename DataType>
class BSTreeNode {
 public:
  /// @brief BSTree is a friend class to allow access to private members.
  friend class BSTree<DataType>;

  /// @brief Default constructor.
  BSTreeNode() = default;

  /**
   * @brief Constructor with parameters.
   * @param value The key to store in the node.
   * @param parent Pointer to the parent node (default nullptr).
   * @param left Pointer to the left child node (default nullptr).
   * @param right Pointer to the right child node (default nullptr).
   */
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr);

  /// @brief Destructor.
  ~BSTreeNode();

  /// @brief Gets the key value stored in the node.
  /// @return The key.
  DataType getKey() const;

  /// @brief Gets the parent pointer.
  /// @return Pointer to the parent node.
  BSTreeNode<DataType> *getParent() const;

  /// @brief Gets the left child pointer.
  /// @return Pointer to the left child node.
  BSTreeNode<DataType> *getLeft() const;

  /// @brief Gets the right child pointer.
  /// @return Pointer to the right child node.
  BSTreeNode<DataType> *getRight() const;

  /// @brief Sets the parent pointer.
  /// @param parent Pointer to the new parent node.
  void setParent(BSTreeNode<DataType> *parent);

  /// @brief Sets the left child pointer.
  /// @param left Pointer to the new left child node.
  void setLeft(BSTreeNode<DataType> *left);

  /// @brief Sets the right child pointer.
  /// @param right Pointer to the new right child node.
  void setRight(BSTreeNode<DataType> *right);

 private:
  DataType key; ///< The key stored in the node.

  BSTreeNode<DataType> *parent = nullptr; ///< Pointer to the parent node.
  BSTreeNode<DataType> *left = nullptr;   ///< Pointer to the left child.
  BSTreeNode<DataType> *right = nullptr;  ///< Pointer to the right child.
};

/**
 * @class BSTree
 * @brief Binary Search Tree implementation.
 * @tparam DataType The type of data stored in the tree.
 */
template <typename DataType>
class BSTree {
 public:
  /// @brief Default constructor.
  BSTree() = default;

  /// @brief Destructor.
  ~BSTree() {};

  /**
   * @brief Inserts a value into the BST.
   * @param value The value to insert.
   */
  void insert(const DataType &value);

  /**
   * @brief Removes a value from the BST.
   * @param value The value to remove.
   */
  void remove(const DataType &value);

  /**
   * @brief Performs an inorder traversal starting from a subtree root.
   * @param rootOfSubtree The root node of the subtree.
   */
  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Performs a preorder traversal starting from a subtree root.
   * @param rootOfSubtree The root node of the subtree.
   */
  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Performs a postorder traversal starting from a subtree root.
   * @param rootOfSubtree The root node of the subtree.
   */
  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Searches for a value in a subtree.
   * @param rootOfSubtree The root node of the subtree.
   * @param value The value to search for.
   * @return Pointer to the node containing the value, or nullptr if not found.
   */
  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  /**
   * @brief Finds the node with the minimum key in a subtree.
   * @param rootOfSubtree The root node of the subtree.
   * @return Pointer to the node with the minimum key.
   */
  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Finds the node with the maximum key in a subtree.
   * @param rootOfSubtree The root node of the subtree.
   * @return Pointer to the node with the maximum key.
   */
  BSTreeNode<DataType> *getMaximum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Finds the in-order successor of a given node.
   * @param node The node whose successor is to be found.
   * @return Pointer to the successor node.
   */
  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const;

  /**
   * @brief Gets the root of the BST.
   * @return Pointer to the root node.
   */
  BSTreeNode<DataType> *getRoot() const;

  /**
   * @brief Inserts multiple values to create a balanced tree quickly.
   * @param n The number of values to insert.
   */
  void fastInsert(size_t n);
  
 private:
  BSTreeNode<DataType> *root; ///< Pointer to the root of the BST.

  /**
   * @brief Builds a balanced subtree for fast insertion.
   * @param start Starting key value.
   * @param end Ending key value.
   * @param parent Pointer to the parent node.
   * @return Pointer to the root of the new balanced subtree.
   */
  BSTreeNode<DataType>* buildBalancedSubtree(DataType start, DataType end, BSTreeNode<DataType>* parent);

  /**
   * @brief Replaces one subtree with another.
   * @param u The subtree to be replaced.
   * @param v The replacement subtree.
   */
  void transplant(BSTreeNode<DataType> *u, BSTreeNode<DataType> *v);
};
