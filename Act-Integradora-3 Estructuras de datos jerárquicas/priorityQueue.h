#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>

template <class T>
class PriorityQueueHandler {
public:
    // Función para contabilizar accesos y almacenar en un Binary Heap
    static std::priority_queue<std::pair<int, T>> contabilizarAccesos(const std::vector<T>& elementos);

    // Función para obtener el elemento con mayor número de accesos
    static std::pair<int, T> obtenerIPConMayorAccesos(std::priority_queue<std::pair<int, T>>& heap);

    // Función para obtener la IP con el menor número de accesos mayor o igual a un valor
    static std::pair<int, T> obtenerIPConAccesosMinimos(std::priority_queue<std::pair<int, T>> heap, int minimoAccesos);
};

// Implementación de contabilizarAccesos
template <class T>
std::priority_queue<std::pair<int, T>> PriorityQueueHandler<T>::contabilizarAccesos(const std::vector<T>& elementos) {
    std::unordered_map<T, int> contador;

    // Contar las repeticiones de cada elemento
    for (const auto& elemento : elementos) {
        contador[elemento]++;
    }

    // Crear un Binary Heap (Priority Queue) basado en las frecuencias
    std::priority_queue<std::pair<int, T>> heap;
    for (const auto& par : contador) {
        heap.push({par.second, par.first}); // Insertar {frecuencia, elemento}
    }

    return heap;
}

// Implementación de obtenerIPConMayorAccesos
template <class T>
std::pair<int, T> PriorityQueueHandler<T>::obtenerIPConMayorAccesos(std::priority_queue<std::pair<int, T>>& heap) {
    if (!heap.empty()) {
        return heap.top(); // Retornar el elemento con mayor frecuencia
    }
    return {0, T()}; // Si el heap está vacío, retornar un par vacío
}

// Implementación de obtenerIPConAccesosMinimos
template <class T>
std::pair<int, T> PriorityQueueHandler<T>::obtenerIPConAccesosMinimos(std::priority_queue<std::pair<int, T>> heap, int minimoAccesos) {
    std::pair<int, T> resultado = {0, T()}; // Inicializar con un par vacío
    while (!heap.empty()) {
        auto top = heap.top();
        heap.pop();
        if (top.first >= minimoAccesos) {
            resultado = top; // Guardar el primer elemento que cumpla la condición
        }
    }
    return resultado; // Retornar el resultado
}

#endif // PRIORITYQUEUE_H