#include "MensajeEmisor.h"
#include <sstream>

MensajeEmisor::MensajeEmisor(int codigo) : Mensaje(codigo) {}

// Setters y Getters de atributos específicos
void MensajeEmisor::setUsuario(const std::string& usuario) {
    id_usuario = usuario;
}

std::string MensajeEmisor::getUsuario() const {
    return id_usuario;
}

void MensajeEmisor::setDispositivo(const std::string& dispositivo) {
    id_dispositivo = dispositivo;
}

std::string MensajeEmisor::getDispositivo() const {
    return id_dispositivo;
}

// Serialización Sobreescrita: incluye IDs específicos
std::string MensajeEmisor::serializar() const {
    std::ostringstream oss;
    // Añadir campos específicos
    oss << "Usuario:" << id_usuario << ";";
    oss << "Dispositivo:" << id_dispositivo << ";";
    
    // Usar la serialización de la clase base para el resto de los datos (código y mapa)
    oss << Mensaje::serializar();
    return oss.str();
}

// Deserialización Sobreescrita: extrae IDs y luego usa la lógica base
bool MensajeEmisor::deserializar(const std::string& data) {
    // 1. Limpiar atributos específicos
    id_usuario.clear();
    id_dispositivo.clear();
    
    // 2. Parsear IDs y reconstruir la cadena para la base
    std::string data_restante;
    std::istringstream iss(data);
    std::string token;

    while (std::getline(iss, token, ';')) {
        if (token.rfind("Usuario:", 0) == 0) {
            id_usuario = token.substr(8);
        } else if (token.rfind("Dispositivo:", 0) == 0) {
            id_dispositivo = token.substr(12);
        } else {
            // Reconstruir la cadena con tokens que la clase base debe parsear (código y datos)
            data_restante += token + ";";
        }
    }

    // 3. Dejar que la clase base (Mensaje) se encargue del código de operación y el mapa de datos
    return Mensaje::deserializar(data_restante);
}