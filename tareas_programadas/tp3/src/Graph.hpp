#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include <string>
#include <tuple>

// Clase que representa la estructura del grafo
class Graph {
 public:
  Graph() = default;
  // Constructor
  void addEdge(const std::string& from, const std::string& to, int weight);
  // Agrega una arista entre dos nodos con un peso dado
  void buildFromEdges(const std::vector<std::tuple<std::string, std::string, int>>& edges);
  // Construye el grafo a partir de las tuplas
  void printAdjacencyList() const;
  // Imprime la lista de adyacencia 

  const std::map<std::string, std::vector<std::pair<std::string, int>>>& getAdjacency() const;
  const std::vector<std::string>& getNodes() const;
  const std::map<std::string, int>& getNodeIndex() const;
  // Métodos para acceder a datos internos para análisis

 private:
  void addNode(const std::string& name);
  // Añade un nodo al grafo si no existe
  std::map<std::string, std::vector<std::pair<std::string, int>>> adjacency;
  // Mapa con nodos y lista de adyacencia
  std::vector<std::string> nodes;
  // Lista de nombres de nodos para orden y acceso rápido por índice
  std::map<std::string, int> nodeIndex;
  // Mapa para obtener índice del nodo dado su nombre (para matrices)

};

#endif
