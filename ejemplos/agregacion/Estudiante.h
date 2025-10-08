#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H
#include <string>
#include <vector>
#include "Libro.h"

class Estudiante {
    std::string nombre;
    std::vector<Libro*> librosPrestados;  // libro es un atributo
    //vector de punteros a libros
    /*aca el vector desaparece con el estudiante pero los libros siguen existiendo*/
public:
    explicit Estudiante(std::string n);
    void prestarLibro(Libro* libro);
    void devolverLibro(Libro* libro);
    void mostrarLibrosPrestados() const;
    const std::string& getNombre() const;
};

#endif