#ifndef FORMATO_318_H
#define FORMATO_318_H

#include <string>
#include <vector>

class Formato_318 {
public:
    virtual ~Formato_318() = default;

    // Convierte datos recibidos del Arduino a CSV
    virtual std::vector<std::string> convertirACsv(const std::vector<std::string>& datos) = 0;

    // Convierte datos almacenados en CSV a otro formato (o el mismo)
    virtual std::string convertirDeCsv(const std::vector<std::string>& datos) = 0;
};

#endif
