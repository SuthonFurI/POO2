#include "Formato_318.h"
#include <sstream>

std::vector<std::string> Formato_318::convertirACsv(const std::vector<std::string>& datos, char formato) {
    // Si ya es CSV, devolver igual
    if (formato == 'c') return datos;

    // TODO: implementar parser JSON/XML → CSV real
    // Por ahora devolvemos los datos tal cual
    return datos;
}

std::string Formato_318::convertirDeCsv(const std::vector<std::string>& datos, char formato) {
    std::ostringstream out;
    if (formato == 'c') {
        for (auto& linea : datos) out << linea << "\n";
    }
    else if (formato == 'j') {
        out << "[\n";
        for (auto& linea : datos) out << "  \"" << linea << "\",\n";
        out << "]\n";
    }
    else if (formato == 'x') {
        out << "<datos>\n";
        for (auto& linea : datos) out << "  <linea>" << linea << "</linea>\n";
        out << "</datos>\n";
    }
    return out.str();
}
