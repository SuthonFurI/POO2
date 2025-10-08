#ifndef PROFESOR_H
#define PROFESOR_H
#include <string>
#include "Curso.h"

class Profesor {
    std::string nombre;
public:
    explicit Profesor(std::string n);
    void darClase(const Curso& curso) const; /*asociacion simple
    curso es un parametro, no un atributo*/
};

#endif
