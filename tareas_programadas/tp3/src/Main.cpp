#include "Menu.hpp"

/**
 * @brief Función principal que crea un objeto Menu con un archivo de entrada
 *        y ejecuta el menú principal.
 * 
 * @return int Código de salida del programa.
 */
int main() {
    Menu menu("test/input_large.csv");
    menu.run();
    return 0;
}
