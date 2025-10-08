#include "FormatoJSON_318.h"
#include <sstream>

std::vector<std::string> FormatoJSON_318::convertirACsv(const std::vector<std::string>& datos) {
    // TODO: parsear JSON real -> CSV
    // Por ahora devolvemos igual que recibimos (mock)
    return datos;
}

std::string FormatoJSON_318::convertirDeCsv(const std::vector<std::string>& datos) {
    std::ostringstream out;
    out << "[\n";
    for (auto& linea : datos) {
        out << "  \"" << linea << "\",\n";
    }
    out << "]\n";
    return out.str();
}
