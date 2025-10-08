#ifndef MOTO_H
#define MOTO_H

#include "Vehiculo.h"

class Moto : public Vehiculo {
    bool tieneSidecar;

public:
    Moto(string m, int a, bool sidecar);
    void mostrarDatos() const override;
};

#endif
