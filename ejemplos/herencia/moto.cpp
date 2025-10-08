#include "Moto.h"
#include <iostream>
using namespace std;

Moto::Moto(string m, int a, bool sidecar)
    : Vehiculo(m, a), tieneSidecar(sidecar) {}

void Moto::mostrarDatos() const {
    cout << "[MOTO] ";
    Vehiculo::mostrarDatos();
    cout << "Sidecar: " << (tieneSidecar ? "Sí" : "No") << endl;
}
