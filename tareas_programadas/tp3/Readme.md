# ci0116_25a_c20281

Tarea 3

## Estudiante:
- Alexa Alpízar Mora, C20281

## Tabla de Contenidos

-   Instalación
-   Manual de Usuario y Descripción de la Tarea
-   Interacción con el Programa

## Instalación

Para compilar este código, primero asegúrate de tener instalado:

  • Visual Studio Code (con extensiones de C/C++) para ejecutar el código.  
  • Make o MakeTools para compilar con el Makefile.

## Manual de Usuario

### Descripción de la Tarea

 El objetivo de la tarea es utilizar teoría de grafos y algoritmos asociados aplicados a la resolución
 de un problema específico. Se espera que la persona estudiante sea capaz de analizar el problema y
 diseñar una solución utilizando el conocimiento adquirido a partir del estudio de los algoritmos de
 grafos vistos en el curso.

### ¿Cómo usarlo?

Para ejecutar este programa, sigue los siguientes pasos:

1. Busca al usuario aalpizarmora en Github, copia la URL del repositorio y clónalo en tu terminal.

```bash
git clone https://github.com/aalpizarmora/concurrente25a-Alexa_Alpizar.git

```

2. Navega al directorio del repositorio.

```bash

  cd ci0116_25a_c20281/tareas_programadas/tp3
```

3. Actualiza los últimos cambios del repositorio.

```bash

  git pull origin main
```
4. Finalmente, para abrirlo en Visual Studio Code, usa el siguiente comando:

```bash

  code .
```
### Ejecutar el Programa

Abre la terminal de Visual Studio y ejecuta (por ejemplo):

```bash
  make clean
  make
  bin/tp3
  
```
## Interacción con el programa

### Selección del archivo de entrada

El programa ya cuenta con un archivo para probar y correr el programa. Sin embargo, de ser necesario, antes de ejecutar el programa puede indicar en el archivo "Main.cpp" el archivo que desee de los disponibles.

Parte del archivo "Main.cpp":

```bash

int main() 
    Menu menu("test/input_large.csv");
    menu.run();
    return 0;

```

Archivos disponibles:

```bash

test/input_small.csv

test/input_medium.csv

test/input_large.csv
```

### Menú de Interacción
Al ejecutar el programa, se despliega un menú de opciones numeradas que permite al usuario interactuar con las funcionalidades del sistema. El usuario debe ingresar el número correspondiente a la pregunta que desea consultar. 

Las opciones disponibles son:

1. Encontrar la ciudad centro.
Calcula la ciudad o ciudades con la menor suma de distancias hacia todas las demás (centro de distribución ideal).

2. Encontrar mejor ciudad para despachar a un destino.
El usuario deberá ingresar el nombre de una ciudad destino, y el programa indicará cuál(es) ciudad(es) puede(n) despachar suministros en el menor tiempo posible hacia ese destino.

3. Encontrar ciudades más distantes.
Determina los pares de ciudades con la mayor distancia posible, junto con su ruta más corta.

4. Encontrar ciudades más cercanas.
Busca y muestra el par o los pares de ciudades con la menor distancia entre ellas.

5. Ranking de ciudades por distancia promedio.
Lista las ciudades ordenadas de menor a mayor según el tiempo promedio que les toma llegar a otras ciudades.

O en caso de desear salir del programa debe oprimir:

0. Salir
Finaliza la ejecución del programa.


Sin importar la(s) opcion(es) que eliga, se generará un archivo .csv con su respuesta y podrá observarla en la carpeta "output" dento del mismo proyecto donde se encuentra (tp3).

```bash

  cd ci0116_25a_c20281/tareas_programadas/tp3/output
```

## Creditos
Alexa Alpízar Mora


