#include "FormatoXML_318.h"
#include <sstream>

std::vector<std::string> FormatoXML_318::convertirACsv(const std::vector<std::string>& datos) {
    // TODO: parsear XML real -> CSV
    // Por ahora devolvemos igual que recibimos (mock)
    return datos;
}

std::string FormatoXML_318::convertirDeCsv(const std::vector<std::string>& datos) {
    std::ostringstream out;
    out << "<datos>\n";
    for (auto& linea : datos) {
        out << "  <linea>" << linea << "</linea>\n";
    }
    out << "</datos>\n";
    return out.str();
}

