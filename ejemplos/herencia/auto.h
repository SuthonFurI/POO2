#ifndef AUTO_H
#define AUTO_H

#include "Vehiculo.h"

class Auto : public Vehiculo {
    int puertas;

public:
    Auto(string m, int a, int p);
    void mostrarDatos() const override;
    // override indica que sobreescribe un metodo virtual de la clase base
};

#endif
