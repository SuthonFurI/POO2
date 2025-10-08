#ifndef MENSAJE_RECEPTOR_H
#define MENSAJE_RECEPTOR_H

#include "Mensaje.h"

// Clase que representa el mensaje simple (código + datos)
class MensajeReceptor : public Mensaje {
public:
    MensajeReceptor(int codigo = 0);
    // Hereda serializar(), deserializar() y persistencia de Mensaje
};

#endif
