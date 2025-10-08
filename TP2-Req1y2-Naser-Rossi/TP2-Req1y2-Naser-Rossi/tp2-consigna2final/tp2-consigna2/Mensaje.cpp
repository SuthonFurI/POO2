#include "Mensaje.h"
#include <sstream>
#include <utility>
#include <iostream>
#include <fstream>

// Implementación del Helper para inferir el tipo
Valor Mensaje::parseValor(const std::string& str) {
    try {
        // Intentar parsear como entero
        size_t pos;
        int i = std::stoi(str, &pos);
        if (pos == str.length()) { return i; }
    } catch (...) {}

    try {
        // Intentar parsear como doble
        size_t pos;
        double d = std::stod(str, &pos);
        if (pos == str.length()) { return d; }
    } catch (...) {}

    // Si falla la conversión numérica, se asume que es una cadena
    return str;
}

Mensaje::Mensaje(int codigo) : codigoOperacion(codigo) {}

void Mensaje::setCodigoOperacion(int codigo) { codigoOperacion = codigo; }
int Mensaje::getCodigoOperacion() const { return codigoOperacion; }

void Mensaje::agregarDato(const std::string& clave, const Valor& valor) {
    datos[clave] = valor;
}

Valor Mensaje::obtenerDato(const std::string& clave) const {
    auto it = datos.find(clave);
    if (it != datos.end()) return it->second;
    return std::string(""); 
}

std::string Mensaje::serializar() const {
    std::ostringstream oss;
    oss << "Operacion:" << codigoOperacion << ";";

    for (const auto& [k, v] : datos) {
        oss << k << "=";
        std::visit([&oss](auto&& arg) { oss << arg; }, v);
        oss << ";";
    }
    return oss.str();
}

bool Mensaje::deserializar(const std::string& data) {
    datos.clear();
    std::istringstream iss(data);
    std::string token;

    while (std::getline(iss, token, ';')) {
        if (token.rfind("Operacion:", 0) == 0) {
            try {
                codigoOperacion = std::stoi(token.substr(10));
            } catch (...) { return false; }
        } else if (!token.empty()) {
            auto pos = token.find('=');
            if (pos != std::string::npos) {
                std::string clave = token.substr(0, pos);
                std::string valor = token.substr(pos + 1);
                datos[clave] = parseValor(valor);
            }
        }
    }
    return true;
}

bool Mensaje::guardarEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;
    archivo << serializar();
    archivo.close();
    return true;
}

bool Mensaje::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;
    std::string linea;
    std::getline(archivo, linea);
    archivo.close();
    return deserializar(linea);
}

Mensaje::~Mensaje() {}
