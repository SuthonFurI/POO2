#ifndef MOTOR_H
#define MOTOR_H
#include <string>
#include <iostream>

class Motor {
    int potencia;
public:
    explicit Motor(int p) : potencia(p) {}
    void encender() const {
        std::cout << "Motor encendido con " << potencia << " HP" << std::endl;
    }
    int getPotencia() const { return potencia; }
};

#endif
