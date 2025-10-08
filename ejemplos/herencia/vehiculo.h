#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
using namespace std;

class Vehiculo {
protected:
    string marca;
    int anio;

public:
    Vehiculo(string m, int a);
    virtual void mostrarDatos() const;
    //virtual para polimorfismo, elijo la version correcta
    //en tiempo de ejecucion (version hijo)
    virtual ~Vehiculo() {} // destructor virtual
};

#endif
