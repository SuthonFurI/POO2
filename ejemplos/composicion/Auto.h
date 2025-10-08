#ifndef AUTO_H
#define AUTO_H
#include <string>
#include "Motor.h"

class Auto {
    std::string marca;
    Motor motor;  // 🔹 Composición: el auto contiene su propio motor
public:
    Auto(std::string m, int pot);
    void arrancar() const;
};

#endif
