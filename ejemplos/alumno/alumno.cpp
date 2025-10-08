#include "alumno.h"
#include <iostream>


Alumno::Alumno(std::string n, int leg, float p){
    nombre = n;
    legajo = leg;
    promedio = p;
}

void Alumno::mostrar(){
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Legajo: " << legajo << std::endl;
    std::cout << "Promedio: " << promedio << std::endl;
}
//.\programa.exe
