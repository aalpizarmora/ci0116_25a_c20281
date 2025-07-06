#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>
#include <vector>
#include <tuple>

/**
 * @class FileReader
 * @brief Clase utilitaria para leer archivos CSV que contienen datos de aristas.
 */
class FileReader {
    // Clase para leer el archivo .csv y extraer los datos de las aristas(edges).
 public:
  /**
   * @brief Lee un archivo CSV y extrae la información de las aristas.
   * @param filename Nombre del archivo CSV a leer.
   * @return Un vector de tuplas, cada una con dos nombres de nodos y un peso entero.
   */
  static std::vector<std::tuple<std::string, std::string, int>>
  // Vector de tuplas que contiene 2 strings y un entero.
  readCSV(const std::string& filename);
  // Función para leer el archivo.
};

#endif
