#include <iostream>
#include "Auto.h"
#include "Moto.h"
using namespace std;

int main() {
    Auto a1("Toyota", 2020, 4);
    Moto m1("Yamaha", 2022, false);

    a1.mostrarDatos();
    cout << endl;
    m1.mostrarDatos();

    return 0;
}
