#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>
#include "Excepcion.h"

class Alumno {
private:
    std::string nombre;
    int legajo;
    float promedio;

public:
    Alumno(const std::string& n, int l, float p); // puede lanzar ValidacionError

    void setPromedio(float p);                    // puede lanzar ValidacionError
    float getPromedio() const;
    const std::string& getNombre() const;
    int getLegajo() const;
};

#endif
