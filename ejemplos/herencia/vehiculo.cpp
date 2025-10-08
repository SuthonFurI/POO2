#include "Vehiculo.h"
#include <iostream>
using namespace std;

Vehiculo::Vehiculo(string m, int a) : marca(m), anio(a) {}

void Vehiculo::mostrarDatos() const {
    cout << "Marca: " << marca << ", Año: " << anio << endl;
}
