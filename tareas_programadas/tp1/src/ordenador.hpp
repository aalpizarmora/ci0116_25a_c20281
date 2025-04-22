#ifndef ordenador_hpp
#define ordenador_hpp

#pragma once
#include <utility>


/*
Credits
Author: Prof. Arturo Camacho, Universidad de Costa Rica
 
Modified by: Prof. Allan Berrocal, Universidad de Costa Rica
*/

class Ordenador {
    private:
    // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
    // Puede definir cuantos metodos quiera.
      
      // Metodo auxiliar para el ordenamiento por mezcla
      void mezcla(int* A, int l, int m, int r) const;
      void mergeSort(int* A, int l, int r) const;

      // Metodo auxiliar para el ordenamiento por monticulos
      void heapify(int* A, int n, int i) const;

      // Metodo auxiliar para el ordenamiento rapido
      int partition(int* A, int low, int high) const;
      void quickSort(int* A, int low, int high) const;
    
    public:
    Ordenador() = default;
    ~Ordenador() = default;

    /* Nota:
     - Si no planea implementar algunos de los métodos de ordenamiento, no los borre.
     - Simplemente déjelos con el cuerpo vacío para evitar errores de compilación, ya
       que se ejecutará el mismo main para todas las tareas.
     - Recuerde hacer uso de programación defensiva y documentar los métodos con formato Doxygen, por ejemplo.
     - No cambié la firma de los métodos de la clase Ordenador.
     - No lance excepciones para el manejo de errores.
       Ante un error, basta con que el método no modifique el arreglo original y que no cause la caída del programa.
    */ 
    void ordenamientoPorSeleccion(int *A, int n) const;
    void ordenamientoPorInserccion(int *A, int n) const;
    void ordenamientoPorMezcla(int *A, int n) const;
    void ordenamientoPorMonticulos(int *A, int n) const;
    void ordenamientoRapido(int *A, int n) const;
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

  int* L = new int[n1];
  int* R = new int[n2];

  for (int i = 0; i < n1; i++)
      L[i] = A[l + i];
  for (int j = 0; j < n2; j++)
      R[j] = A[m + 1 + j];

  int i = 0, j = 0, k = l;

  while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
          A[k++] = L[i++];
      } else {
          A[k++] = R[j++];
      }
  }

  while (i < n1) A[k++] = L[i++];
  while (j < n2) A[k++] = R[j++];

  delete[] L;
  delete[] R;
}
void Ordenador::mergeSort(int* A, int l, int r) const {
  if (l < r) {
      int m = l + (r - l) / 2;
      mergeSort(A, l, m);
      mergeSort(A, m + 1, r);
      mezcla(A, l, m, r);
  }
}
void Ordenador::heapify(int* A, int n, int i) const {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && A[l] > A[largest])
      largest = l;

  if (r < n && A[r] > A[largest])
      largest = r;

  if (largest != i) {
      std::swap(A[i], A[largest]);
      heapify(A, n, largest);
  }
}
int Ordenador::partition(int* A, int low, int high) const {
  int pivot = A[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
      if (A[j] < pivot) {
          ++i;
          std::swap(A[i], A[j]);
      }
  }

  std::swap(A[i + 1], A[high]);
  return i + 1;
  }

void Ordenador::quickSort(int* A, int low, int high) const {
if (low < high) {
    int pi = partition(A, low, high);
    quickSort(A, low, pi - 1);
    quickSort(A, pi + 1, high);
}
}
void Ordenador::ordenamientoPorSeleccion(int *A, int n) const {
  if (!A || n <= 0) return;
  for (int i = 0; i < n - 1; ++i) {
      int minIdx = i;
      for (int j = i + 1; j < n; ++j) {
          if (A[j] < A[minIdx]) {
              minIdx = j;
          }
      }
      std::swap(A[i], A[minIdx]);
  }
}
void Ordenador::ordenamientoPorInserccion(int *A, int n) const {
  if (!A || n <= 0) return;
  for (int i = 1; i < n; ++i) {
      int key = A[i];
      int j = i - 1;
      while (j >= 0 && A[j] > key) {
          A[j + 1] = A[j];
          --j;
      }
      A[j + 1] = key;
  }
}
void Ordenador::ordenamientoPorMezcla(int *A, int n) const {
  if (!A || n <= 0) return;
  mergeSort(A, 0, n - 1);
}
void Ordenador::ordenamientoPorMonticulos(int *A, int n) const {
  if (!A || n <= 0) return;
  for (int i = n / 2 - 1; i >= 0; --i)
      heapify(A, n, i);
  for (int i = n - 1; i > 0; --i) {
      std::swap(A[0], A[i]);
      heapify(A, i, 0);
  }
}
void Ordenador::ordenamientoRapido(int *A, int n) const {
  if (!A || n <= 0) return;
  quickSort(A, 0, n - 1);
}
void Ordenador::ordenamientoPorResiduos(int *A, int n) const {
  if (!A || n <= 0) return;

  int maxVal = A[0];
  for (int i = 1; i < n; ++i)
      if (A[i] > maxVal) maxVal = A[i];

  for (int exp = 1; maxVal / exp > 0; exp *= 10) {
      int output[n];
      int count[10] = {0};

      for (int i = 0; i < n; ++i)
          count[(A[i] / exp) % 10]++;

      for (int i = 1; i < 10; ++i)
          count[i] += count[i - 1];

      for (int i = n - 1; i >= 0; --i) {
          output[count[(A[i] / exp) % 10] - 1] = A[i];
          count[(A[i] / exp) % 10]--;
      }

      for (int i = 0; i < n; ++i)
          A[i] = output[i];
  }
}
#endif // ORDENADOR_HPP