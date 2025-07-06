#include "Menu.hpp"
#include "File_Reader.hpp"

#include <iostream>
#include <string>
#include <limits>

using namespace std;

Menu::Menu(const std::string& csvFile)
    : analyzer(graph) {
        // Inicializa analyzer con la referencia a graph
    auto edges = FileReader::readCSV(csvFile);
    // Lee las aristas desde el archivo CSV

    if (edges.empty()) {
        // Verifica si no se leyeron aristas
        cerr << "Error: No se pudieron leer aristas del archivo: " << csvFile << endl;  // Mensaje de error
        exit(1);
        // Termina el programa con error
    }

    graph.buildFromEdges(edges);
    // Construye el grafo con las aristas leídas
}

// Muestra menú principal
void Menu::displayOptions() {
    cout << "\n----- Menú -----\n";
    cout << "1. Ciudad más cercana de todas las demás, donde es más efectivo colocar el equipo.\n";
    cout << "2. Ciudad más cercana para despachar suministros.\n";
    cout << "3. Par de ciudades más distantes.\n";
    cout << "4. Par de ciudades más cercanas.\n";
    cout << "5. Lista de ciudades ordenadas por tiempo promedio.\n";
    cout << "0. Salir.\n";
    cout << "Opción: ";
}

void Menu::processOption(int option) {
    switch (option) {
        case 1:
            cout << "\n[1] Ciudad central:\n";
            analyzer.findCenter();
            break;

        case 2: {
            cout << "\n[2] Ciudad más cercana para despachar suministros:\n";
            cout << "Ingrese el nombre de la ciudad destino: ";
            string destino;
            cin.ignore();
            // Limpia buffer de entrada antes de getline
            getline(cin, destino);
            // Lee el nombre de la ciudad destino

            if (graph.getNodeIndex().count(destino) == 0) {
                // Verifica si la ciudad no existe
                cout << "La ciudad '" << destino << "' no existe en el grafo.\n";
            } else {
                analyzer.findBestDispatchCity(destino);
                // Busca mejor ciudad para despachar
            }
            break;
        }

        case 3:
            cout << "\n[3] Se ha generado un archivo que indica las ciudades más distantes (carpeta output):\n";  // Info opción 3
            analyzer.findMostDistantCities();
            // Ejecuta función para ciudades más distantes
            break;

        case 4:
            cout << "\n[4] Se ha generado un archivo que indica las ciudades más cercanas (carpeta output):\n";  // Info opción 4
            analyzer.findClosestCities();
            // Ejecuta función para ciudades más cercanas
            break;

        case 5:
            cout << "\n[5] Ranking creciente por tiempo promedio:\n";
            analyzer.rankCitiesByAverageDistance();
            // Muestra ciudades ordenadas por tiempo promedio
            break;

        default:
            cout << "Opción inválida, intente de nuevo:) \n";
    }
}

void Menu::run() {
    int option;
    do {
        displayOptions();
        // Muestra el menú al usuario
        cin >> option;
        // Lee opción ingresada

        if (cin.fail()) {
            // Verifica si hubo error de entrada
            cin.clear();
            // Limpia el estado de error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Descarta entrada inválida
            cout << "Opción inválida. Intente de nuevo.\n";
            // Mensaje error
            continue;
            // Vuelve a mostrar el menú
        }

        if (option == 0) {
            // Si la opción es 0, salir del programa
            cout << "Has salido.\n";
            break;
        }

        processOption(option);
        // Procesa la opción ingresada

    } while (true);
    // Repite indefinidamente hasta salir
}
