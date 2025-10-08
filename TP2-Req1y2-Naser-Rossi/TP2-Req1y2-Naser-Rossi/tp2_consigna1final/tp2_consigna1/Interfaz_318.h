#ifndef INTERFAZ_318_H
#define INTERFAZ_318_H

#include <string>
#include <vector>
#include "Archivo_318.h"

class Interfaz_318 {
public:
    Interfaz_318() = default;
    void ejecutar(const std::string& archivoNombre, bool modoLectura, const std::vector<std::string>& datos);
};

#endif
