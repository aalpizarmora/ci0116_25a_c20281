#include "Menu.hpp"
#include "File_Reader.hpp"

#include <iostream>
#include <string>
#include <limits>

using namespace std;

Menu::Menu(const std::string& csvFile)
    : analyzer(graph) {
    auto edges = FileReader::readCSV(csvFile);

    if (edges.empty()) {
        cerr << "Error: No se pudieron leer aristas del archivo: " << csvFile << endl;
        exit(1);
    }

    graph.buildFromEdges(edges);
}

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
            getline(cin, destino);

            if (graph.getNodeIndex().count(destino) == 0) {
                cout << "La ciudad '" << destino << "' no existe en el grafo.\n";
            } else {
                analyzer.findBestDispatchCity(destino);
            }
            break;
        }

        case 3:
            cout << "\n[3] Se ha generado un archivo que indica las ciudades más distantes (carpeta output):\n";
            analyzer.findMostDistantCities();
            break;

        case 4:
            cout << "\n[4] Se ha generado un archivo que indica las ciudades más cercanas (carpeta output):\n";
            analyzer.findClosestCities();
            break;

        case 5:
            cout << "\n[5] Ranking creciente por tiempo promedio:\n";
            analyzer.rankCitiesByAverageDistance();
            break;

        default:
            cout << "Opción inválida, intente de nuevo:) \n";
    }
}

void Menu::run() {
    int option;
    do {
        displayOptions();
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Opción inválida. Intente de nuevo.\n";
            continue;
        }

        if (option == 0) {
            cout << "Has salido.\n";
            break;
        }

        processOption(option);

    } while (true);
}
