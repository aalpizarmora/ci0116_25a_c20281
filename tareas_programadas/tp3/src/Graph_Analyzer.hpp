#ifndef GRAPH_ANALYZER_HPP
#define GRAPH_ANALYZER_HPP

#include "Graph.hpp"
#include <vector>
#include <string>

// Clase encargada del análisis y algoritmos sobre el grafo
class GraphAnalyzer {
 public:
  GraphAnalyzer(const Graph& graph);
  // Constructor recibe una referencia al grafo a analizar
  void floydWarshall();
  // Ejecuta el algoritmo Floyd-Warshall para calcular distancias mínimas
  void printDistanceMatrix() const;
  // Imprime la matriz de distancias calculadas

  std::vector<std::string> reconstructPath(int u, int v) const;
  // Reconstruye la ruta entre dos nodos a partir de la matriz de predecesores

  void findCenter() const;
  // Función para encontrar la ciudad más crecana de todas(el centro)
  void findBestDispatchCity(const std::string& destino) const;
  // Encuentra mejor ciudad para despachar suministros a una ciudad destino
  void findMostDistantCities() const;
  // Función para encontrar las ciudades más lejanas entre ellas
  void findClosestCities() const;
  // Función para encontrar las ciudades más cercanas entre ellas
  void rankCitiesByAverageDistance() const;
  // Función para listar las ciudades por distancia 
  


 private:
  const Graph& graph; 
  // Referencia al grafo original
  std::vector<std::vector<int>> distMatrix;
  // Matriz de distancias mínimas
  std::vector<std::vector<int>> predecessor;
  // Matriz para reconstruir caminos
  bool floydComputed = false;
  // Para indicar si ya se calculó Floyd
  void ensureFloydComputed() const;
  // Ejecuta Floyd si no ha sido calculado aún (uso interno)

};

#endif
