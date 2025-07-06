#include "Graph.hpp"
#include <iostream>

// Añade un nodo si no existe en nodeIndex y nodes
void Graph::addNode(const std::string& name) {
    if (nodeIndex.find(name) == nodeIndex.end()) {
        nodeIndex[name] = nodes.size();  // Guarda índice del nuevo nodo
        nodes.push_back(name);           // Añade el nombre a la lista
    }
}

// Añade una arista entre "from" y "to" con peso "weight"
void Graph::addEdge(const std::string& from, const std::string& to, int weight) {
    addNode(from);  // Asegura que ambos nodos existen
    addNode(to);
    adjacency[from].emplace_back(to, weight);  // Añade vecino con peso
}

// Construye el grafo a partir de una lista de aristas
void Graph::buildFromEdges(const std::vector<std::tuple<std::string, std::string, int>>& edges) {
    for (const auto& [from, to, weight] : edges) {
        addEdge(from, to, weight);
    }
}

// Imprime la lista de adyacencia para visualizar el grafo
void Graph::printAdjacencyList() const {
    std::cout << "\nLista de Adyacencia:\n";
    for (const auto& [from, neighbors] : adjacency) {
        std::cout << from << " -> ";
        for (const auto& [to, weight] : neighbors) {
            std::cout << to << "(" << weight << ") ";
        }
        std::cout << "\n";
    }
}

// Métodos que devuelven referencias a los datos internos (solo lectura)
const std::map<std::string, std::vector<std::pair<std::string, int>>>& Graph::getAdjacency() const {
    return adjacency;
}

const std::vector<std::string>& Graph::getNodes() const {
    return nodes;
}

const std::map<std::string, int>& Graph::getNodeIndex() const {
    return nodeIndex;
}
