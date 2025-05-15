#ifndef BITACORA_HEAP_H
#define BITACORA_HEAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class BitacoraHeap {
private:
    std::vector<std::string> datos; // Vector para almacenar los datos del archivo

public:
    // Constructor
    BitacoraHeap() = default;

    // Método para cargar datos desde un archivo
    void cargarDesdeArchivo(const std::string& nombreArchivo);

    // Método para mostrar los datos almacenados
    void mostrarDatos() const;

    // Método para obtener los datos (opcional)
    const std::vector<std::string>& obtenerDatos() const;
};

// Implementación de los métodos fuera de la clase

void BitacoraHeap::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Abrir el archivo en modo lectura
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) { // Leer línea por línea
        std::cout << "Leyendo línea: " << linea << std::endl; // Depuración
        datos.push_back(linea); // Almacenar cada línea en el vector
    }

    archivo.close(); // Cerrar el archivo
    std::cout << "Archivo cargado con éxito. Total de líneas: " << datos.size() << std::endl;
}

void BitacoraHeap::mostrarDatos() const {
    for (const auto& linea : datos) {
        std::cout << linea << std::endl; // Mostrar cada línea almacenada
    }
}

const std::vector<std::string>& BitacoraHeap::obtenerDatos() const {
    return datos; // Retornar el vector de datos
}


#endif // BITACORA_HEAP_H
#endif // BITACORA_HEAP_H