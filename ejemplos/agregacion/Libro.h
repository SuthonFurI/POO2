#ifndef LIBRO_H
#define LIBRO_H
#include <string>

class Libro {
    std::string titulo;
    std::string autor;
public:
    Libro(std::string t, std::string a);
    const std::string& getTitulo() const;
    const std::string& getAutor() const;
    void mostrarInfo() const;
};

#endif