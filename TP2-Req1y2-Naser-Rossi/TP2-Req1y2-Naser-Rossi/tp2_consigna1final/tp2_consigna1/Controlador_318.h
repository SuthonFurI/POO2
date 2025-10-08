#ifndef CONTROLADOR_318_H
#define CONTROLADOR_318_H

#include <string>
#include <vector>

class Controlador_318 {
private:
    std::string puertoSerie;

public:
    Controlador_318(const std::string& puerto = "/dev/ttyUSB0");
    std::vector<std::string> recibirDatos(int cantidad, char formato);
};

#endif

