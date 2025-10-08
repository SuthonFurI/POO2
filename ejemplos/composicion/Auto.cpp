#include "Auto.h"
#include <iostream>
#include <utility>

Auto::Auto(std::string m, int pot)
    : marca(std::move(m)), motor(pot) // 🔹 Se crea el motor dentro del auto
{}

void Auto::arrancar() const {
    std::cout << "El " << marca << " está arrancando..." << std::endl;
    motor.encender();  // El auto usa su motor interno
}
