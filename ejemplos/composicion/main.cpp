#include "Auto.h"

int main() {
    Auto a("Toyota", 120);
    a.arrancar();

    // No hay delete ni punteros.
    // Cuando el objeto 'a' se destruye, su motor también.
    return 0;
}
