#ifndef ordenador_hpp
#define ordenador_hpp

#pragma once
#include <utility>
#include <cmath>

/*
Credits
Author: Prof. Arturo Camacho, Universidad de Costa Rica
 
Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

class Ordenador {
private:
    // Métodos auxiliares de ordenamiento

    /**
     * @brief Realiza la mezcla de dos subarreglos ordenados.
     */
    void mezcla(int* A, int l, int m, int r) const;

    /**
     * @brief Implementa el algoritmo merge sort.
     */
    void mergeSort(int* A, int l, int r) const;

    /**
     * @brief Reorganiza el subárbol para mantener la propiedad de montículo.
     */
    void heapify(int* A, int n, int i) const;

    /**
     * @brief Reorganiza los elementos alrededor de un pivote.
     */
    int partition(int* A, int low, int high) const;

    /**
     * @brief Implementa el algoritmo quick sort.
     */
    void quickSort(int* A, int low, int high) const;

    /**
     * @brief Algoritmo auxiliar para ordenamiento por residuos (radix sort).
     */
    void counting_sort(int* A, int block_size, int num_blocks, int n) const;

public:
    Ordenador() = default;
    ~Ordenador() = default;

    /**
     * @brief Ordena un arreglo utilizando el algoritmo de selección.
     */
    void ordenamientoPorSeleccion(int *A, int n) const;

    /**
     * @brief Ordena un arreglo utilizando el algoritmo de inserción.
     */
    void ordenamientoPorInserccion(int *A, int n) const;

    /**
     * @brief Ordena un arreglo utilizando el algoritmo de mezcla (merge sort).
     */
    void ordenamientoPorMezcla(int *A, int n) const;

    /**
     * @brief Ordena un arreglo utilizando el algoritmo de montículos (heap sort).
     */
    void ordenamientoPorMonticulos(int *A, int n) const;

    /**
     * @brief Ordena un arreglo utilizando el algoritmo rápido (quick sort).
     */
    void ordenamientoRapido(int *A, int n) const;

    /**
     * @brief Ordena un arreglo utilizando el algoritmo de residuos (radix sort).
     */
    void ordenamientoPorResiduos(int *A, int n) const;

    /**
     * @brief Retorna un std::string con los datos de la tarea.
     * 
     * Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
     * 
     * @return std::string Una cadena de texto con los datos de la tarea.
     */
    constexpr const char* imprimirDatosDeTarea() const {
        return "Carné: C20281, Nombre: Alexa Alpízar Mora, Tarea 1";
    }
};

void Ordenador::mezcla(int* A, int l, int m, int r) const {
  int n1 = m - l + 1;
  int n2 = r - m;

  int* L = new int[n1];  // Array auxiliar para la primera mitad
  int* R = new int[n2];  // Array auxiliar para la segunda mitad

  // Copiar los datos a los arrays auxiliares
  for (int i = 0; i < n1; i++)
      L[i] = A[l + i];
  for (int j = 0; j < n2; j++)
      R[j] = A[m + 1 + j];

  int i = 0, j = 0, k = l;

  // Mezclar los dos arrays ordenados
  while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
          A[k++] = L[i++];  // Colocar el elemento más pequeño en A
      } else {
          A[k++] = R[j++];  // Colocar el elemento más pequeño en A
      }
  }

  // Copiar el resto de los elementos
  while (i < n1) A[k++] = L[i++];
  while (j < n2) A[k++] = R[j++];

  // Liberar la memoria de los arrays auxiliares
  delete[] L;
  delete[] R;
}

void Ordenador::mergeSort(int* A, int l, int r) const {
  if (l < r) {
      int m = l + (r - l) / 2;  // Encontrar el punto medio
      mergeSort(A, l, m);        // Ordenar la primera mitad
      mergeSort(A, m + 1, r);    // Ordenar la segunda mitad
      mezcla(A, l, m, r);        // Mezclar las dos mitades
  }
}

void Ordenador::heapify(int* A, int n, int i) const {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  // Verificar si el hijo izquierdo es más grande
  if (l < n && A[l] > A[largest])
      largest = l;

  // Verificar si el hijo derecho es más grande
  if (r < n && A[r] > A[largest])
      largest = r;

  // Intercambiar y continuar con el heapify si es necesario
  if (largest != i) {
      std::swap(A[i], A[largest]);
      heapify(A, n, largest);  // Llamada recursiva
  }
}

int Ordenador::partition(int* A, int low, int high) const {
  int pivot = A[high];  // El último elemento es el pivote
  int i = low - 1;

  // Reorganizar los elementos alrededor del pivote
  for (int j = low; j < high; j++) {
      if (A[j] < pivot) {
          ++i;
          std::swap(A[i], A[j]);
      }
  }

  // Colocar el pivote en la posición correcta
  std::swap(A[i + 1], A[high]);
  return i + 1;  // Retornar la posición del pivote
}

void Ordenador::quickSort(int* A, int low, int high) const {
  if (low < high) {
      int pi = partition(A, low, high);  // Particionar el array
      quickSort(A, low, pi - 1);         // Ordenar la parte izquierda
      quickSort(A, pi + 1, high);        // Ordenar la parte derecha
  }
}

void Ordenador::ordenamientoPorSeleccion(int *A, int n) const {
  if (!A || n <= 0) return;
  for (int i = 0; i < n - 1; ++i) {
      int minIdx = i;
      // Buscar el mínimo en el resto del array
      for (int j = i + 1; j < n; ++j) {
          if (A[j] < A[minIdx]) {
              minIdx = j;
          }
      }
      // Intercambiar el mínimo encontrado con la posición actual
      std::swap(A[i], A[minIdx]);
  }
}

void Ordenador::ordenamientoPorInserccion(int *A, int n) const {
  if (!A || n <= 0) return;
  for (int i = 1; i < n; ++i) {
      int key = A[i];
      int j = i - 1;
      // Mover los elementos mayores que key hacia una posición adelante
      while (j >= 0 && A[j] > key) {
          A[j + 1] = A[j];
          --j;
      }
      A[j + 1] = key;  // Insertar key en su lugar
  }
}

void Ordenador::ordenamientoPorMezcla(int *A, int n) const {
  if (!A || n <= 0) return;
  mergeSort(A, 0, n - 1);  // Llamar a mergeSort para ordenar
}

void Ordenador::ordenamientoPorMonticulos(int *A, int n) const {
  if (!A || n <= 0) return;
  // Construir el heap
  for (int i = n / 2 - 1; i >= 0; --i)
      heapify(A, n, i);
  // Extraer el máximo y reconstruir el heap
  for (int i = n - 1; i > 0; --i) {
      std::swap(A[0], A[i]);
      heapify(A, i, 0);  // Llamada recursiva
  }
}

void Ordenador::ordenamientoRapido(int *A, int n) const {
  if (!A || n <= 0) return;
  quickSort(A, 0, n - 1);  // Llamar a quickSort para ordenar
}

void Ordenador::counting_sort(int* A, int block_size, int num_blocks, int n) const {
  int* output = new int[n];               // Array auxiliar para almacenar los resultados
  int* count = new int[num_blocks]();     // Array para contar la frecuencia de cada bloque

  // Contar las ocurrencias de cada bloque
  for (int i = 0; i < n; ++i) {
      int block = (A[i] >> (block_size * i)) & ((1 << block_size) - 1);  // Extraer el bloque
      count[block]++;
  }

  // Modificar count para tener la frecuencia acumulada de los bloques
  for (int i = 1; i < num_blocks; ++i) {
      count[i] += count[i - 1];
  }

  // Colocar los elementos en el array de salida
  for (int i = n - 1; i >= 0; --i) {
      int block = (A[i] >> (block_size * i)) & ((1 << block_size) - 1);
      output[--count[block]] = A[i];
  }

  // Copiar los elementos ordenados de output a A
  for (int i = 0; i < n; ++i) {
      A[i] = output[i];
  }

  delete[] output;  // Liberar memoria del array auxiliar
  delete[] count;   // Liberar memoria del array de conteo
}

void Ordenador::ordenamientoPorResiduos(int *A, int n) const {
  if (!A || n <= 0) return;

  int r = std::floor(std::log2(n));   // Tamaño del bloque en bits
  int numBits = 32;                   // Supone enteros de 32 bits
  int d = (numBits + r - 1) / r;      // Número de bloques necesarios

  // Ordenar por cada bloque de bits
  for (int i = 0; i < d; ++i) {
      counting_sort(A, r, (1 << r), n);  // Llamada al counting_sort con los parámetros adecuados
  }
}

#endif // ORDENADOR_HPP
