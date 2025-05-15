#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

//Codigo extraido de:: https://www.geeksforgeeks.org/heap-sort/

template <class T>
class HeapSorter {
public:
    // Función para extraer las IPs de un archivo
    static std::vector<std::string> extraerIPs(const std::string& nombreArchivo);

    // Función para ordenar las IPs usando Heap Sort
    static void heapSort(std::vector<std::string>& data);

    // Función para escribir las IPs ordenadas en un archivo
    static void escribirIPs(const std::string& nombreArchivo, const std::vector<std::string>& ips);

private:
    // Función auxiliar para hacer el heapify
    static void heapify(std::vector<std::string>& data, int n, int i);

    // Función para extraer la clave de comparación (puede ser personalizada)
    static std::string extractKey(const std::string& record);
};

// Implementación de extraerIPs
template <class T>
std::vector<std::string> HeapSorter<T>::extraerIPs(const std::string& nombreArchivo) {
    std::vector<std::string> ips;
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    // Expresión regular para extraer la IP (sin puerto)
    std::regex ipRegex(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))");

    if (archivo.is_open()) {
        while (std::getline(archivo, linea)) {
            std::smatch match;
            if (std::regex_search(linea, match, ipRegex)) {
                ips.push_back(match[1]); // Extraer solo la IP (sin puerto)
            }
        }
        archivo.close();
    }

    return ips;
}

// Implementación de heapify
template <class T>
void HeapSorter<T>::heapify(std::vector<std::string>& data, int n, int i) {
    int largest = i; // Inicializar el nodo más grande como raíz
    int left = 2 * i + 1; // Hijo izquierdo
    int right = 2 * i + 2; // Hijo derecho

    // Comparar el hijo izquierdo con la raíz
    if (left < n && extractKey(data[left]) > extractKey(data[largest])) {
        largest = left;
    }

    // Comparar el hijo derecho con el más grande hasta ahora
    if (right < n && extractKey(data[right]) > extractKey(data[largest])) {
        largest = right;
    }

    // Si el más grande no es la raíz
    if (largest != i) {
        std::swap(data[i], data[largest]); // Intercambiar

        // Recursivamente heapify el subárbol afectado
        heapify(data, n, largest);
    }
}

// Implementación de heapSort
template <class T>
void HeapSorter<T>::heapSort(std::vector<std::string>& data) {
    int n = data.size();

    // Construir el heap (reorganizar el vector)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(data, n, i);
    }

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--) {
        std::swap(data[0], data[i]); // Mover la raíz actual al final

        // Llamar a heapify en el heap reducido
        heapify(data, i, 0);
    }
}

// Implementación de escribirIPs
template <class T>
void HeapSorter<T>::escribirIPs(const std::string& nombreArchivo, const std::vector<std::string>& ips) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const auto& ip : ips) {
            archivo << ip << std::endl;
        }
        archivo.close();
    }
}

// Implementación de extractKey
template <class T>
std::string HeapSorter<T>::extractKey(const std::string& record) {
    return record; // Por defecto, la clave es el mismo registro
}

#endif // HEAPSORT_H