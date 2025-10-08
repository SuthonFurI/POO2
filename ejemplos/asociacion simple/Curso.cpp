#include "Curso.h"
#include <utility>

Curso::Curso(std::string n) : nombre(std::move(n)) {}

const std::string& Curso::getNombre() const {
    return nombre;
}
