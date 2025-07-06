#ifndef GRAPH_ANALYZER_HPP
#define GRAPH_ANALYZER_HPP

#include "Graph.hpp"
#include <vector>
#include <string>

/**
 * @class GraphAnalyzer
 * @brief Responsible for analyzing a graph and applying graph algorithms.
 */
class GraphAnalyzer {
 public:
  /**
   * @brief Constructor that receives a reference to the graph to analyze.
   * @param graph The graph to analyze.
   */
  GraphAnalyzer(const Graph& graph);

  /**
   * @brief Runs the Floyd-Warshall algorithm to compute all-pairs shortest paths.
   */
  void floydWarshall();

  /**
   * @brief Prints the computed distance matrix.
   */
  void printDistanceMatrix() const;

  /**
   * @brief Reconstructs the shortest path from node u to node v using the predecessor matrix.
   * @param u Index of the source node.
   * @param v Index of the target node.
   * @return Vector of node names representing the reconstructed path from u to v.
   */
  std::vector<std::string> reconstructPath(int u, int v) const;

  /**
   * @brief Finds the most central city (node with the smallest total distance to all others).
   */
  void findCenter() const;

  /**
   * @brief Finds the best city from which to dispatch supplies to a destination city.
   * @param destino The name of the destination city.
   */
  void findBestDispatchCity(const std::string& destino) const;

  /**
   * @brief Finds the pair of cities that are the farthest apart (maximum shortest path).
   */
  void findMostDistantCities() const;

  /**
   * @brief Finds the pair of cities that are closest to each other (minimum shortest path).
   */
  void findClosestCities() const;

  /**
   * @brief Lists all cities sorted by their average distance to all other cities.
   */
  void rankCitiesByAverageDistance() const;

 private:
  /**
   * @brief Reference to the graph to be analyzed.
   */
  const Graph& graph;

  /**
   * @brief Matrix of shortest distances between all pairs of nodes.
   */
  std::vector<std::vector<int>> distMatrix;

  /**
   * @brief Matrix used to reconstruct shortest paths between nodes.
   */
  std::vector<std::vector<int>> predecessor;

  /**
   * @brief Flag that indicates whether the Floyd-Warshall algorithm has already been run.
   */
  bool floydComputed = false;

  /**
   * @brief Ensures the Floyd-Warshall algorithm has been executed before using distance data.
   */
  void ensureFloydComputed() const;
};

#endif
