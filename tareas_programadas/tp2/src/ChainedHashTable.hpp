/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>

#include "DoublyLinkedList.hpp"

/**
 * @brief A chained hash table implementation using doubly linked lists for collision resolution.
 * 
 * @tparam DataType The type of elements stored in the hash table.
 */
template <typename DataType>
class ChainedHashTable {
 public:
  /**
   * @brief Constructs a chained hash table with a given number of buckets.
   * 
   * @param size Number of buckets in the hash table.
   */
  ChainedHashTable(size_t size);

  /**
   * @brief Destructor for the hash table.
   * Automatically cleans up the underlying linked lists.
   */
  ~ChainedHashTable() {};

  /**
   * @brief Inserts a value into the hash table if it does not already exist.
   * 
   * @param value The value to insert.
   */
  void insert(const DataType& value);

  /**
   * @brief Searches for a value in the hash table.
   * 
   * @param value The value to search for.
   * @return Pointer to the node containing the value if found, nullptr otherwise.
   */
  DLListNode<DataType>* search(const DataType& value) const;

  /**
   * @brief Removes all occurrences of a value from the hash table.
   * 
   * @param value The value to remove.
   */
  void remove(const DataType& value);

  /**
   * @brief Gets the number of buckets in the hash table.
   * 
   * @return Number of buckets.
   */
  size_t getSize() const;

  /**
   * @brief Returns a copy of the internal vector of doubly linked lists representing the buckets.
   * 
   * @return Vector of doubly linked lists.
   */
  std::vector<DLList<DataType>> getTable() const;

  /**
   * @brief Replaces the internal vector of buckets with a new one.
   * Also updates the size accordingly.
   * 
   * @param newTable New vector of doubly linked lists.
   */
  void setTable(std::vector<DLList<DataType>>);

 private:
  size_t size; ///< Number of buckets in the hash table.

  std::vector<DLList<DataType>> table; ///< Vector of doubly linked lists used as buckets.
};
