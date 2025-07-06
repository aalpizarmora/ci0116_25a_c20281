#ifndef MENU_HPP
#define MENU_HPP

#include "Graph.hpp"
#include "Graph_Analyzer.hpp"

/**
 * @class Menu
 * @brief Clase que maneja la interacción con el usuario y controla el flujo del programa.
 */
class Menu {
 public:
  /**
   * @brief Constructor que recibe el nombre del archivo CSV para cargar el grafo.
   * @param csvFile Nombre del archivo CSV con los datos de las aristas.
   */
  Menu(const std::string& csvFile);

  /**
   * @brief Método principal que ejecuta el menú y procesa las opciones del usuario.
   */
  void run();

 private:
  /**
   * @brief Grafo que contiene los nodos y aristas.
   */
  Graph graph;

  /**
   * @brief Analizador que aplica algoritmos sobre el grafo.
   */
  GraphAnalyzer analyzer;

  /**
   * @brief Muestra las opciones disponibles en el menú.
   */
  void displayOptions();

  /**
   * @brief Procesa la opción seleccionada por el usuario.
   * @param option Opción ingresada por el usuario.
   */
  void processOption(int option);
};

#endif
