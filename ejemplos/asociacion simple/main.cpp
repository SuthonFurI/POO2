#include <iostream>
#include "Profesor.h"
#include "Curso.h"

int main() {
    Profesor prof("Julieta Rossi");
    Curso poo("Programación Orientada a Objetos");
    Curso termodinamica("Termodinámica");

    // Asociación simple: el profesor usa el curso solo al momento de dar clase
    prof.darClase(poo);
    prof.darClase(termodinamica);

    std::cout << "\nAmbos objetos existen por separado.\n";
    return 0;
}
