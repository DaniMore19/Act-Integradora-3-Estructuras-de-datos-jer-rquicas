#include "heapSort.h"
#include "priorityQueue.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Especialización de extractKey para std::string
template <>
std::string HeapSorter<std::string>::extractKey(const std::string &record) {
  // Buscar el primer espacio o ':' para extraer la IP
  size_t colonPos = record.find(':');
  return (colonPos != std::string::npos) ? record.substr(0, colonPos) : record;
}

int main() {
  std::string archivoEntrada = "bitacoraHeap.txt";
  std::string archivoSalida = "bitacora_ordenada.txt";
  std::string archivoTopIPs = "ips_con_mayor_acceso.txt";

  // Extraer las IPs del archivo de bitácora
  std::vector<std::string> ips = HeapSorter<std::string>::extraerIPs(archivoEntrada);

  // Ordenar las IPs
  HeapSorter<std::string>::heapSort(ips);

  // Escribir las IPs ordenadas en un archivo
  HeapSorter<std::string>::escribirIPs(archivoSalida, ips);

  // Contabilizar accesos y almacenar en un Binary Heap
  auto heap = PriorityQueueHandler<std::string>::contabilizarAccesos(ips);

  // Obtener la IP con mayor número de accesos
  auto ipMayorAccesos = PriorityQueueHandler<std::string>::obtenerIPConMayorAccesos(heap);

  std::cout << "Las IPs han sido extraídas y ordenadas correctamente." << std::endl;
  std::cout << "La IP con mayor número de accesos es: " << ipMayorAccesos.second
            << " con " << ipMayorAccesos.first << " accesos." << std::endl;

  // Encontrar las diez IPs con más accesos
  std::ofstream archivoTop(archivoTopIPs);
  if (!archivoTop.is_open()) {
    std::cerr << "Error al abrir el archivo para escribir las IPs con más accesos." << std::endl;
    return 1;
  }

  archivoTop << "Top 10 IPs con más accesos:\n";
  std::cout << "\nTop 10 IPs con más accesos:\n";

  auto heapCopia = heap; // Crear una copia del heap para no consumir el original
  for (int i = 0; i < 10 && !heapCopia.empty(); ++i) {
    auto topIP = heapCopia.top();
    heapCopia.pop();
    std::cout << topIP.second << " con " << topIP.first << " accesos." << std::endl;
    archivoTop << topIP.second << " con " << topIP.first << " accesos.\n";
  }

  archivoTop.close();

  // Obtener la IP con el menor número de accesos mayor o igual a 3
  auto ipConAccesosMinimos = PriorityQueueHandler<std::string>::obtenerIPConAccesosMinimos(heap, 3);
  if (ipConAccesosMinimos.first > 0) {
    std::cout << "\nLa IP con el menor número de accesos mayor o igual a 3 es: "
              << ipConAccesosMinimos.second << " con " << ipConAccesosMinimos.first << " accesos." << std::endl;
  } else {
    std::cout << "\nNo se encontró ninguna IP con accesos mayores o iguales a 3." << std::endl;
  }

  return 0;
}