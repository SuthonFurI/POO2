#include "pieza.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept> // para std::invalid_argument

static const double PI = std::acos(-1.0);
using namespace std;

Pieza::Pieza(int id_) : id(id_) {}
int Pieza::getId() const { return id; }

// Rectangular
Rectangular::Rectangular(int id_, double ancho_, double alto_)
    : Pieza(id_), ancho(ancho_), alto(alto_) {
    if (ancho_ <= 0.0 || alto_ <= 0.0) {
        throw std::invalid_argument("Rectangulo: ancho y alto deben ser > 0");
    }
}
double Rectangular::getSuperficie() const { return ancho * alto; }
std::string Rectangular::descripcion() const {
    std::ostringstream os;
    cout << "Rectangulo (w=" << ancho << ", h=" << alto << ")"<< endl;
    return os.str();
}

// Circular
Circular::Circular(int id_, double radio_)
    : Pieza(id_), radio(radio_) {
    if (radio_ <= 0.0) {
        throw std::invalid_argument("Circulo: radio debe ser > 0");
    }
}
double Circular::getSuperficie() const { return PI * radio * radio; }
std::string Circular::descripcion() const {
    std::ostringstream os;
    cout << "Circulo (r=" << radio << ")"<< endl;
    return os.str();
}

// Triangular equilátera
TriangularEquilatera::TriangularEquilatera(int id_, double lado_)
    : Pieza(id_), lado(lado_) {
    if (lado_ <= 0.0) {
        throw std::invalid_argument("Triangulo: lado debe ser > 0");
    }
}
double TriangularEquilatera::getSuperficie() const {
    return (std::sqrt(3.0) / 4.0) * lado * lado;
}
std::string TriangularEquilatera::descripcion() const {
    std::ostringstream os;
    cout << "Triangulo equilatero (a=" << lado << ")"<< endl;
    return os.str();
}