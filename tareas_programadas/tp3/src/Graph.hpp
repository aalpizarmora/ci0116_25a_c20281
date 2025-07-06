#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include <string>
#include <tuple>

/**
 * @class Graph
 * @brief Clase que representa la estructura del grafo.
 */
class Graph {
 public:
  Graph() = default;
  /**
   * @brief Agrega una arista entre dos nodos con un peso dado.
   * @param from Nombre del nodo origen.
   * @param to Nombre del nodo destino.
   * @param weight Peso de la arista.
   */
  void addEdge(const std::string& from, const std::string& to, int weight);
  /**
   * @brief Construye el grafo a partir de un vector de tuplas que representan aristas.
   * @param edges Vector de tuplas con (nodo_origen, nodo_destino, peso).
   */
  void buildFromEdges(const std::vector<std::tuple<std::string, std::string, int>>& edges);
  /**
   * @brief Imprime la lista de adyacencia del grafo.
   */
  void printAdjacencyList() const;

  /**
   * @brief Obtiene la lista de adyacencia.
   * @return Referencia constante al mapa de adyacencia.
   */
  const std::map<std::string, std::vector<std::pair<std::string, int>>>& getAdjacency() const;

  /**
   * @brief Obtiene la lista de nodos.
   * @return Referencia constante al vector de nombres de nodos.
   */
  const std::vector<std::string>& getNodes() const;

  /**
   * @brief Obtiene el mapa de índices de nodos.
   * @return Referencia constante al mapa que asocia nombres de nodos con índices.
   */
  const std::map<std::string, int>& getNodeIndex() const;

 private:
  /**
   * @brief Añade un nodo al grafo si no existe.
   * @param name Nombre del nodo a añadir.
   */
  void addNode(const std::string& name);

  /**
   * @brief Mapa que asocia cada nodo con su lista de adyacencia (pares de nodo destino y peso).
   */
  std::map<std::string, std::vector<std::pair<std::string, int>>> adjacency;

  /**
   * @brief Vector con la lista de nombres de nodos para mantener orden y acceso rápido.
   */
  std::vector<std::string> nodes;

  /**
   * @brief Mapa para obtener el índice de un nodo dado su nombre (útil para matrices).
   */
  std::map<std::string, int> nodeIndex;
};

#endif
