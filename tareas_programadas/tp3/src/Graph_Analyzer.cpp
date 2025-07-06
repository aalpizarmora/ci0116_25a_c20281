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

// Imprime la matriz de distancias mínimas calculadas
void GraphAnalyzer::printDistanceMatrix() const {
    ensureFloydComputed();
    const int INF = std::numeric_limits<int>::max() / 2;
    const std::vector<std::string>& nodes = graph.getNodes();
    int n = (int)nodes.size();

    std::cout << "\nMatriz de distancias mínimas (Floyd-Warshall):\n";
    std::cout << std::setw(12) << " ";
    for (const std::string& name : nodes)
        std::cout << std::setw(12) << name;
    std::cout << "\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(12) << nodes[i];
        for (int j = 0; j < n; ++j) {
            if (distMatrix[i][j] == INF)
                std::cout << std::setw(12) << "INF";
            else
                std::cout << std::setw(12) << distMatrix[i][j];
        }
        std::cout << "\n";
    }
}

// Reconstruye la ruta más corta entre dos nodos usando la matriz de predecesores
std::vector<std::string> GraphAnalyzer::reconstructPath(int u, int v) const {
    std::vector<std::string> path;
    if (predecessor[u][v] == -1) return path; 
    // No hay camino

    const auto& nodes = graph.getNodes();
    int current = v;

    // Sigue los predecesores hacia atrás hasta llegar a u
    while (current != u) {
        path.push_back(nodes[current]);
        current = predecessor[u][current];
    }
    path.push_back(nodes[u]);

    std::reverse(path.begin(), path.end()); 
    // Invierte para que vaya de u a v
    return path;
}

// Encuentra el nodo "centro" con suma mínima de distancias a todos los demás
void GraphAnalyzer::findCenter() const {
    ensureFloydComputed();  
    // Asegura que la matriz de distancias esté calculada
    const int INF = std::numeric_limits<int>::max() / 2;  
    // Valor que representa infinito (mitad para evitar overflow al sumar)
    const std::vector<std::string>& nodes = graph.getNodes();  
    // Obtiene los nombres de los nodos (ciudades)
    int n = (int)nodes.size();  
    // Número total de nodos en el grafo
    int minSum = INF;  
    // Guarda la suma mínima de distancias encontrada
    std::vector<int> centers;  
    // Vector para guardar los índices de los nodos centro

    for (int i = 0; i < n; ++i) {  
        // Recorre cada nodo como posible centro
        int sum = 0;  
        // Suma de distancias desde el nodo 
        bool reachable = true;  
        // Indica si el nodo puede alcanzar a todos los demás

        for (int j = 0; j < n; ++j) {  
            // Recorre los demás nodos para sumar distancias

            if (distMatrix[i][j] >= INF) {  
                // Si no hay camino entre i y j
                reachable = false;  
                // Marca como no alcanzable
                break;  
                // Sale del ciclo
            }
            sum += distMatrix[i][j];  
            // Suma la distancia entre i y j
        }

        if (reachable) {  
            // Si el nodo i alcanza a todos los demás

            if (sum < minSum) {  
                // Si es una nueva suma mínima
                minSum = sum;  
                // Actualiza la suma mínima
                centers.clear();  
                // Limpia la lista de centros anteriores
                centers.push_back(i);  
                // Añade el nuevo nodo centro
            } else if (sum == minSum) {  
                // Si tiene la misma suma mínima
                centers.push_back(i);  
                // Añade como centro adicional
            }
        }
    }

    if (!centers.empty()) {  
        // Si hay al menos un nodo centro
        std::cout << "\nLa ciudad con menor duración (" << minSum << ") hacia las demás es:\n";  
        // Imprime el encabezado con la suma mínima

        for (int i : centers) {  
            // Recorre los nodos centro encontrados
            std::cout << " - " << nodes[i] << "\n";  
            // Imprime el nombre del nodo centro
        }
    } else {
        std::cout << "\nNo hay un nodo que alcance a todos los demás.\n";  
        // Si ningún nodo alcanza a todos, imprime mensaje
    }
}


// Encuentra el par de ciudades más distantes
void GraphAnalyzer::findMostDistantCities() const {
    ensureFloydComputed();

    std::ofstream out("output/most_distant_cities.txt"); 
    // Abre archivo de salida para guardar los resultados

    // Verifica si el archivo se abrió correctamente
    if (!out) {
        std::cerr << "Error al abrir archivo de salida.\n";
        // Muestra error si falla
        return;
    }

    std::streambuf* cout_buf = std::cout.rdbuf();
    // Guarda el buffer original de cout
    std::cout.rdbuf(out.rdbuf());
    // Redirige cout al archivo

    const int INF = std::numeric_limits<int>::max() / 2;
    // Valor que representa infinito
    const std::vector<std::string>& nodes = graph.getNodes(); 
    // Obtiene los nombres de las ciudades
    int n = (int)nodes.size(); 
    // Cantidad de nodos en el grafo

    int maxDist = -1;
    // Inicializa la mayor distancia encontrada
    std::vector<std::pair<int, int>> pairs; 
    // Vector para guardar pares con la mayor distancia

    // Recorre todos los pares de nodos
    for (int i = 0; i < n; ++i)  
        for (int j = 0; j < n; ++j)
            if (distMatrix[i][j] < INF && distMatrix[i][j] > maxDist) { 
                // Si hay un nuevo máximo
                maxDist = distMatrix[i][j]; 
                // Actualiza la mayor distancia
                pairs.clear(); 
                // Limpia la lista de pares
                pairs.emplace_back(i, j); 
                // Añade el nuevo par
            } else if (distMatrix[i][j] == maxDist) {
                pairs.emplace_back(i, j);
                // Añade otro par con la misma distancia máxima
            }

    // Si hay pares con la mayor distancia
    if (!pairs.empty()) { 
        std::cout << "\nPares de ciudades más distantes con distancia " << maxDist << ":\n";

        for (auto [u, v] : pairs) { 
            // Recorre los pares
            std::cout << nodes[u] << " -> " << nodes[v] << ": "; 
            // Imprime el nombre del par de ciudades
            auto path = reconstructPath(u, v);
            // Reconstruye el camino más corto entre ellas
            for (size_t i = 0; i < path.size(); ++i) { 
                // Recorre el camino
                std::cout << path[i];
                // Imprime el nombre de la ciudad
                if (i + 1 < path.size()) std::cout << " -> "; 
                // Imprime la flecha si no es el último nodo
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "\nNo hay ciudades conectadas entre sí.\n";
    }

    std::cout.rdbuf(cout_buf);  // Restaura el buffer original de cout
}

// Encuentra el par de ciudades más cercanas (menor distancia mínima)
void GraphAnalyzer::findClosestCities() const {
    ensureFloydComputed();

    // Abre archivo de salida para guardar los resultados
    std::ofstream out("output/closest_cities.txt");
    if (!out) {
        // Si no se puede abrir el archivo, se muestra un error y se termina
        std::cerr << "Error al abrir archivo de salida.\n";
        return;
    }

    std::streambuf* cout_buf = std::cout.rdbuf();
    // Guarda el buffer original de cout (para poder restaurarlo después)
    std::cout.rdbuf(out.rdbuf());
    // Redirige la salida estándar al archivo de salida
    const int INF = std::numeric_limits<int>::max() / 2;
    // Define el valor que representa infinito
    const std::vector<std::string>& nodes = graph.getNodes();
    // Obtiene la lista de nombres de ciudades
    int n = (int)nodes.size();
    // Número total de nodos en el grafo
    int minDist = INF;
    // Variable para guardar la menor distancia encontrada

    std::vector<std::pair<int, int>> pairs;
    // Vector para guardar todos los pares (i, j) que tengan la menor distancia

    // Recorre todos los pares de nodos i y j
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            // Solo se consideran pares distintos y caminos finitos
            if (i != j && distMatrix[i][j] < minDist && distMatrix[i][j] < INF) {
                // Se encuentra un nuevo mínimo: actualiza y reinicia la lista
                minDist = distMatrix[i][j];
                pairs.clear();
                pairs.emplace_back(i, j);
            } else if (distMatrix[i][j] == minDist) {
                // Otro par con la misma distancia mínima: se añade a la lista
                pairs.emplace_back(i, j);
            }

    // Si hay al menos un par con distancia mínima
    if (!pairs.empty()) {
        std::cout << "\nPares de ciudades más cercanas con distancia " << minDist << ":\n";

        // Para cada par (u, v), reconstruye e imprime el camino
        for (auto [u, v] : pairs) {
            std::cout << nodes[u] << " -> " << nodes[v] << ": ";

            // Reconstruye el camino más corto entre u y v
            auto path = reconstructPath(u, v);

            // Imprime el camino ciudad por ciudad
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i];
                if (i + 1 < path.size()) std::cout << " -> ";
            }

            std::cout << "\n";
        }
    } else {
        // No se encontró ninguna ciudad conectada
        std::cout << "\nNo hay ciudades conectadas.\n";
    }

    // Restaura el buffer original de cout, vuelve a imprimir en consola
    std::cout.rdbuf(cout_buf);
}


// Ordena las ciudades según el tiempo promedio hacia todas las demás
void GraphAnalyzer::rankCitiesByAverageDistance() const {
    ensureFloydComputed();
    const int INF = std::numeric_limits<int>::max() / 2;
    const auto& nodes = graph.getNodes();
    int n = (int)nodes.size();
    // Cantidad total de ciudades

    std::vector<std::pair<std::string, double>> cityAverages;
    // Vector para almacenar pares (ciudad, promedio de distancias)

    // Calcula el promedio de distancias desde cada ciudad hacia las demás
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        // Suma acumulada de distancias desde la ciudad i
        int count = 0;
        // Cantador de ciudades alcanzables desde la ciudad i

        for (int j = 0; j < n; ++j) {
            // Solo se consideran distancias finitas y distintas de sí misma
            if (i != j && distMatrix[i][j] < INF) {
                sum += distMatrix[i][j];
                ++count;
            }
        }

        // Si hay al menos una ciudad alcanzable, se calcula el promedio
        if (count > 0) {
            double avg = static_cast<double>(sum) / count;
            cityAverages.emplace_back(nodes[i], avg);
        } else {
            // Si no hay ciudades alcanzables, se considera el promedio como infinito
            cityAverages.emplace_back(nodes[i], INF);
        }
    }

    // Ordena las ciudades de menor a mayor según el promedio de distancia
    std::sort(cityAverages.begin(), cityAverages.end(),
              [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                  return a.second < b.second;
              });
    
    // Imprime el resultado
    std::cout << "\nCiudades ordenadas por menor tiempo promedio hacia otras:\n";
    for (const auto& [city, avg] : cityAverages) {
        if (avg >= INF)
            std::cout << city << ": INF\n";
        else
            std::cout << city << ": " << std::fixed << std::setprecision(2) << avg << "\n";
    }
}

// Busca la mejor ciudad para despachar suministros a la ciudad destino
void GraphAnalyzer::findBestDispatchCity(const std::string& destino) const {
    ensureFloydComputed();

    const int INF = std::numeric_limits<int>::max() / 2;
    // Define el valor "infinito" usado como comparación para distancias no alcanzables
    const auto& nodeIndex = graph.getNodeIndex();
    // Obtiene el mapa de nombres de nodos a índices
    const std::vector<std::string>& nodes = graph.getNodes();
    // Obtiene la lista de nombres de nodos en orden

    // Verifica que la ciudad destino exista en el grafo
    if (nodeIndex.find(destino) == nodeIndex.end()) {
        std::cout << "La ciudad '" << destino << "' no existe en el grafo.\n";
        return;
    }

    // Obtiene el índice correspondiente a la ciudad destino
    int destIndex = nodeIndex.at(destino);
    // Inicializa la menor distancia como infinita
    int minTime = INF;
    // Lista para guardar los índices de las ciudades con menor tiempo hacia el destino
    std::vector<int> bestSources;

    // Recorre todos los nodos y busca el que tenga la menor distancia hasta el destino
    for (int i = 0; i < (int)nodes.size(); ++i) {
        if (i == destIndex) continue;
        // Lista para guardar los índices de las ciudades con menor tiempo hacia el destino

        int distance = distMatrix[i][destIndex];
        // Lista para guardar los índices de las ciudades con menor tiempo hacia el destino
        if (distance < minTime) {
            minTime = distance;
            bestSources.clear();
            // Borra candidatos anteriores
            bestSources.push_back(i);
            // Agrega nuevo mejor origen

        // Si hay empate en la menor distancia, agrega otro candidato
        } else if (distance == minTime) {
            bestSources.push_back(i);
        }
    }

    if (minTime == INF) {
        std::cout << "Ninguna ciudad puede alcanzar a '" << destino << "'.\n";
        return;
    }

    std::cout << "Ciudad(es) óptima(s) para despachar suministros a '" << destino 
              << "' (tiempo mínimo: " << minTime << "):\n";

    for (int index : bestSources) {
        std::cout << "- " << nodes[index] << '\n';
    }
    std::cout << "\n";
}