#include "Alumno.h"

static void validarPromedio(float p) {  /*la funcion validar promedio no existe en Alumno.h
    es como que la defino dentro de alumno.cpp pero nadie mas la puede usar
    uso static para reforzar encapuslamiento proque fuera de alumno.cpp no tiene una
    utilidad real*/
    if (p < 0.0f || p > 10.0f) {
        throw ValidacionError("Promedio invalido (debe estar entre 0 y 10)");
    }
}

Alumno::Alumno(const std::string& n, int l, float p) //:: implica que es el constructor de Alumno
    : nombre(n), legajo(l), promedio(0.0f) //inicializo promedio en 0.0 para que no falle 
{
    if (l <= 0) {
        throw ValidacionError("Legajo invalido (debe ser positivo)");
    }
    validarPromedio(p);
    promedio = p;
}

void Alumno::setPromedio(float p) {
    validarPromedio(p);
    promedio = p;
}

float Alumno::getPromedio() const { return promedio; }
const std::string& Alumno::getNombre() const { return nombre; }
int Alumno::getLegajo() const { return legajo; }
