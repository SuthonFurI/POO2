#ifndef MENSAJE_EMISOR_H
#define MENSAJE_EMISOR_H

#include "Mensaje.h"
#include <string>

// Clase que representa el mensaje con IDs específicos (código + datos + usuario + dispositivo)
class MensajeEmisor : public Mensaje {
private:
    // Atributos privados y específicos
    std::string id_usuario;
    std::string id_dispositivo;

public:
    MensajeEmisor(int codigo = 0);

    // Setters y Getters
    void setUsuario(const std::string& usuario);
    std::string getUsuario() const;
    void setDispositivo(const std::string& dispositivo);
    std::string getDispositivo() const;
    
    // Sobreescritura para incluir/extraer los IDs específicos
    std::string serializar() const override;
    bool deserializar(const std::string& data) override;
};

#endif
