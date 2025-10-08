#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>

class Alumno{
    private:
    std::string nombre;
    int legajo;
    float promedio;
    public:
    Alumno(std::string n, int leg, float p);
    void mostrar();
};
#endif

