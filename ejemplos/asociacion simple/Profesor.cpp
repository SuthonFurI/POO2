#include "Profesor.h"
#include <iostream>
#include <utility>

Profesor::Profesor(std::string n) : nombre(std::move(n)) {}

void Profesor::darClase(const Curso& curso) const {
    std::cout << nombre << " está dando la clase de " << curso.getNombre() << std::endl;
}
