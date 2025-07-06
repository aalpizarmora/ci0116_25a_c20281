#include "File_Reader.hpp"
#include <fstream> // Para leer archivos
#include <sstream> // Para procesar texto línea por línea
#include <iostream> // Imprimir errores
#include <vector> //Para usar el vector de tuplas

// Implementación de la función que lee un archivo CSV
std::vector<std::tuple<std::string, std::string, int>>
FileReader::readCSV(const std::string& filename) {
    std::ifstream file(filename);
    // Abre el archivo
    std::vector<std::tuple<std::string, std::string, int>> edges;
    // Guarda los datos leídos
    std::string line;
    // Para leer cada línea

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << "\n";
        return edges;
    }

    std::getline(file, line);
    // Saltar encabezado

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        // Convierte la línea a un stream para separarla por comas
        std::string idSrc, nameSrc, idTgt, nameTgt, weightStr;
        // Variables para guardar cada campo

        // Se extrae cada campo separado por comas
        std::getline(ss, idSrc, ',');
        std::getline(ss, nameSrc, ',');
        std::getline(ss, idTgt, ',');
        std::getline(ss, nameTgt, ',');
        std::getline(ss, weightStr);

        int peso = std::stoi(weightStr);
        // Se convierte a entero
        edges.emplace_back(nameSrc, nameTgt, peso);
        // guarda la tupla en el vector
    }

    return edges;
}
