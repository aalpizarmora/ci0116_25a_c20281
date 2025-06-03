/**
 * @file RBTree.h
 * @brief Red-Black Tree class definition.
 * 
 * Based on the implementation by Prof. Arturo Camacho, Universidad de Costa Rica.
 * Modified by Prof. Allan Berrocal, Universidad de Costa Rica.
 */

#pragma once

/**
 * @enum colors
 * @brief Enum to represent the color of Red-Black Tree nodes.
 */
enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

/**
 * @class RBTreeNode
 * @brief Node class for Red-Black Tree.
 * 
 * @tparam DataType The type of data stored in the tree node.
 */
template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  /**
   * @brief Default constructor.
   */
  RBTreeNode() = default;

  /**
   * @brief Parameterized constructor.
   * @param value The value to store in the node.
   * @param parent Pointer to the parent node.
   * @param left Pointer to the left child.
   * @param right Pointer to the right child.
   * @param c The color of the node (RED or BLACK).
   */
  RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent = nullptr,
             RBTreeNode<DataType> *left = nullptr,
             RBTreeNode<DataType> *right = nullptr, enum colors c = RED);

  /**
   * @brief Destructor.
   */
  ~RBTreeNode();

  /**
   * @brief Get the key stored in the node.
   * @return The key of the node.
   */
  DataType getKey() const;

  /**
   * @brief Get the parent node.
   * @return Pointer to the parent node.
   */
  RBTreeNode<DataType> *getParent() const;

  /**
   * @brief Get the left child.
   * @return Pointer to the left child.
   */
  RBTreeNode<DataType> *getLeft() const;

  /**
   * @brief Get the right child.
   * @return Pointer to the right child.
   */
  RBTreeNode<DataType> *getRight() const;

  /**
   * @brief Set the key of the node.
   * @param key The new key value.
   */
  void setKey(DataType key);

  /**
   * @brief Set the parent node.
   * @param parent Pointer to the new parent.
   */
  void setParent(RBTreeNode<DataType> *parent);

  /**
   * @brief Set the left child.
   * @param left Pointer to the new left child.
   */
  void setLeft(RBTreeNode<DataType> *left);

  /**
   * @brief Set the right child.
   * @param right Pointer to the new right child.
   */
  void setRight(RBTreeNode<DataType> *right);

 private:
  DataType key;                         /**< Key stored in the node */
  RBTreeNode<DataType> *parent;         /**< Pointer to the parent node */
  RBTreeNode<DataType> *left;           /**< Pointer to the left child */
  RBTreeNode<DataType> *right;          /**< Pointer to the right child */
  enum colors color;                    /**< Color of the node */
};

/**
 * @class RBTree
 * @brief Red-Black Tree implementation.
 * 
 * @tparam DataType The type of data stored in the tree.
 */
template <typename DataType>
class RBTree {
 public:
  /**
   * @brief Constructor.
   */
  RBTree() = default;

  /**
   * @brief Destructor.
   */
  ~RBTree() {};

  /**
   * @brief Insert a value into the tree.
   * @param value The value to insert.
   */
  void insert(const DataType &value);

  /**
   * @brief Remove a value from the tree.
   * @param value The value to remove.
   */
  void remove(const DataType &value);

  void setColor(enum colors newColor);

  /**
   * @brief Search for a value in a subtree.
   * @param rootOfSubtree Root of the subtree to search in.
   * @param value The value to search for.
   * @return Pointer to the node containing the value, or nullptr if not found.
   */
  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  /**
   * @brief Get the minimum value in a subtree.
   * @param rootOfSubtree Root of the subtree.
   * @return Pointer to the node with the minimum value.
   */
  RBTreeNode<DataType> *getMinimum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Get the maximum value in a subtree.
   * @param rootOfSubtree Root of the subtree.
   * @return Pointer to the node with the maximum value.
   */
  RBTreeNode<DataType> *getMaximum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  /**
   * @brief Get the successor of a node.
   * @param node The node to find the successor of.
   * @return Pointer to the successor node.
   */
  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const;

  /**
   * @brief Get the root of the tree.
   * @return Pointer to the root node.
   */
  RBTreeNode<DataType> *getRoot() const;

  /**
   * @brief Get the nil (sentinel) node.
   * @return Pointer to the nil node.
   */
  RBTreeNode<DataType> *getNil() const;

 private:
  RBTreeNode<DataType> *root; /**< Root node of the tree */
  RBTreeNode<DataType> *nil;  /**< Sentinel nil node used in the tree */

  // Private helper methods

  /**
   * @brief Perform left rotation around a node.
   * @param x The node to rotate around.
   */
  void leftRotate(RBTreeNode<DataType> *x);

  /**
   * @brief Perform right rotation around a node.
   * @param y The node to rotate around.
   */
  void rightRotate(RBTreeNode<DataType> *y);

  /**
   * @brief Restore Red-Black Tree properties after insertion.
   * @param z The newly inserted node.
   */
  void insertFixup(RBTreeNode<DataType> *z);

  /**
   * @brief Restore Red-Black Tree properties after deletion.
   * @param x The node to start fixing from.
   */
  void deleteFixup(RBTreeNode<DataType> *x);

  /**
   * @brief Replace one subtree as a child of its parent with another subtree.
   * @param u The node to be replaced.
   * @param v The node to replace u.
   */
  void transplant(RBTreeNode<DataType> *u, RBTreeNode<DataType> *v);

  /**
   * @brief Recursively delete nodes in the tree.
   * @param node The root of the subtree to delete.
   */
  void clear(RBTreeNode<DataType>* node);
};
