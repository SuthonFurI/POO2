#include "Auto.h"
#include <iostream>
using namespace std;

Auto::Auto(string m, int a, int p) : Vehiculo(m, a), puertas(p) {}

void Auto::mostrarDatos() const {
    cout << "[AUTO] ";
    Vehiculo::mostrarDatos();
    //imprime marca y año, que ya viene de la clase base
    cout << "Puertas: " << puertas << endl;
}
