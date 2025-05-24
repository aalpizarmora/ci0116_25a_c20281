/*Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

#pragma once

/**
 * @brief Template class for singly linked list.
 * 
 * @tparam DataType Type of data stored in the list nodes.
 */
template <typename DataType>
class SLList;

/**
 * @brief Template class for singly linked list nodes.
 * 
 * @tparam DataType Type of data stored in the node.
 */
template <typename DataType>
class SLListNode {
 public:
  friend class SLList<DataType>;

  /**
   * @brief Default constructor.
   */
  SLListNode();

  /**
   * @brief Constructor with data and next node pointer.
   * @param value Data value to store in the node.
   * @param next Pointer to the next node (default nullptr).
   */
  SLListNode(const DataType& value, SLListNode<DataType>* next = nullptr);

  /**
   * @brief Destructor.
   */
  ~SLListNode();

  /**
   * @brief Gets the data stored in the node.
   * @return DataType Data stored in the node.
   */
  DataType getKey() const;

  /**
   * @brief Gets the pointer to the next node.
   * @return SLListNode<DataType>* Pointer to the next node.
   */
  SLListNode<DataType>* getNext() const;

  /**
   * @brief Sets the data stored in the node.
   * @param key Data to store in the node.
   */
  void setKey(DataType key);

  /**
   * @brief Sets the pointer to the next node.
   * @param newNode Pointer to the new next node.
   */
  void setNext(SLListNode<DataType>* newNode);

 private:
  DataType key; /**< Data stored in the node */
  SLListNode<DataType>* next; /**< Pointer to the next node */
};

/**
 * @brief Template class for singly linked list.
 * 
 * @tparam DataType Type of data stored in the list.
 */
template <typename DataType>
class SLList {
 public:
  /**
   * @brief Constructor, initializes an empty list.
   */
  SLList();

  /**
   * @brief Destructor, releases memory used by the list.
   */
  ~SLList();

  /**
   * @brief Inserts a new value into the list.
   * @param value Data to insert.
   */
  void insert(const DataType& value);

  /**
   * @brief Searches for a node containing a specific value.
   * @param value Data value to search for.
   * @return SLListNode<DataType>* Pointer to the found node or nullptr if not found.
   */
  SLListNode<DataType>* search(const DataType& value) const;

  /**
   * @brief Removes the node with the specified value from the list.
   * @param value Data value to remove.
   */
  void remove(const DataType& value);

  /**
   * @brief Gets the sentinel nil node of the list.
   * @return SLListNode<DataType>* Pointer to the nil node.
   */
  SLListNode<DataType>* getNil() const;
  
 private:
  SLListNode<DataType>* nil; /**< Sentinel nil node for the list */
};
