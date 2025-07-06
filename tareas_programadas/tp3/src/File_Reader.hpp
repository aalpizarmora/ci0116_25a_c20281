#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>
#include <vector>
#include <tuple>

class FileReader {
    // Clase para leer el archivo .csv y extraer los datos de las aristas(edges).
 public:
  static std::vector<std::tuple<std::string, std::string, int>>
  // Vector de tuplas que contiene 2 strings y un entero.
  readCSV(const std::string& filename);
  // Función para leer el archivo.
};

#endif
