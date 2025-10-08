#include "FormatoCSV_318.h"

std::vector<std::string> FormatoCSV_318::convertirACsv(const std::vector<std::string>& datos) {
    // Si los datos ya están en CSV, no hay que tocarlos
    return datos;
}

std::string FormatoCSV_318::convertirDeCsv(const std::vector<std::string>& datos) {
    std::string salida;
    for (auto& linea : datos) {
        salida += linea + "\n";
    }
    return salida;
}
