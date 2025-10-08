#ifndef CURSO_H
#define CURSO_H
#include <string>

class Curso {
    std::string nombre;
public:
    explicit Curso(std::string n);
    const std::string& getNombre() const;
};

#endif
