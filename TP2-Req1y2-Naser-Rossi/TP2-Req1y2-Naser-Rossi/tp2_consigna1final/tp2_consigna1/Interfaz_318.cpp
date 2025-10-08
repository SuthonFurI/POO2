#include "Interfaz_318.h"
#include <iostream>
#include <sstream>

// Convierte un vector<string> a una sola línea CSV
static std::string vectorToCSV(const std::vector<std::string>& datos) {
    std::ostringstream oss;
    for (size_t i = 0; i < datos.size(); ++i) {
        if (i > 0) oss << ",";
        oss << datos[i];
    }
    return oss.str();
}

void Interfaz_318::ejecutar(const std::string& archivoNombre, bool modoLectura, const std::vector<std::string>& datos) {
    Archivo_318 arch(archivoNombre);

    if (modoLectura) {
        if (!arch.exists()) {
            std::cerr << "El archivo no existe.\n";
            return;
        }
        if (arch.open(std::ios::in)) {
            std::cout << "Leyendo archivo:\n";
            std::string linea;
            while (!(linea = arch.getLine()).empty()) {
                std::cout << linea << "\n";
            }
            arch.close();
        }
    } else {
        if (arch.open(std::ios::out)) {
            std::string linea = vectorToCSV(datos);
            arch.write(linea + "\n");
            std::cout << "Datos escritos en " << archivoNombre << "\n";
            arch.close();
        }
    }
}

