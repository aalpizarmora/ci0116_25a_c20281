#include "Graph_Analyzer.hpp"
#include <fstream>
#include <iostream>
#include <streambuf>
#include <iomanip>
#include <limits>
#include <algorithm>

// Constructor que recibe la referencia al grafo a analizar
GraphAnalyzer::GraphAnalyzer(const Graph& graph) : graph(graph) {}

// Algoritmo Floyd-Warshall para calcular todas las distancias mínimas entre las ciudades y predecesores
void GraphAnalyzer::floydWarshall() {
    const int INF = std::numeric_limits<int>::max() / 2;
    // Define un valor "infinito" (usado para representar que no hay conexión entre nodos)
    int n = (int)graph.getNodes().size();
    // Obtiene el número total de nodos del grafo
    distMatrix.assign(n, std::vector<int>(n, INF));
    // Inicializa distancias con INF
    predecessor.assign(n, std::vector<int>(n, -1));
    // Inicializa predecesores
    floydComputed = true;
    // Marca que ya se calculó

    for (int i = 0; i < n; ++i)
        distMatrix[i][i] = 0;
        // Distancia a sí mismo es 0

    const auto& adjacency = graph.getAdjacency();
    // Obtiene la lista de adyacencias del grafo
    const auto& nodeIndex = graph.getNodeIndex();
    // Obtiene el mapa que relaciona los nombres de nodos con sus índices

    // Recorre todas las aristas del grafo para inicializar las distancias directas
    for (const auto& [from, neighbors] : adjacency) {
        int u = nodeIndex.at(from);
        // Obtiene el índice del nodo origen
        for (const auto& [to, weight] : neighbors) {
            // Recorre cada vecino del nodo origen
            int v = nodeIndex.at(to);
            // Obtiene el índice del nodo destino
            distMatrix[u][v] = weight;
            // Guarda el peso de la arista directa en la matriz de distancias
            predecessor[u][v] = u;
            // El predecesor inmediato de v en el camino desde u es u
        }
    }

    // Floyd-Warshall: actualiza distancias mínimas considerando nodos intermedios
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                // Si pasar por k mejora la distancia de i a j, actualiza
                if (distMatrix[i][k] + distMatrix[k][j] < distMatrix[i][j]) {
                    distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
                    // Actualiza la distancia mínima de i a j
                    predecessor[i][j] = predecessor[k][j];
                    // Actualiza el predecesor de j en el nuevo camino más corto desde i
                }
}

// Garantiza que Floyd se ejecute si no se ha hecho antes
void GraphAnalyzer::ensureFloydComputed() const {
    if (!floydComputed) {
        const_cast<GraphAnalyzer*>(this)->floydWarshall();
    }
}
