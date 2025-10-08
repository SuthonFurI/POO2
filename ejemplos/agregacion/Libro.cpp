#include "Libro.h"
#include <iostream>

Libro::Libro(std::string t, std::string a) 
    : titulo(std::move(t)), autor(std::move(a)) {}

const std::string& Libro::getTitulo() const { 
    /*el primer const= no se puede cambiar el valor cuando invoco la funcion desde main
    segundo const= no se puede cambiar ningun atributo de la clase desde esta funcion
    referencia &=mayor eficiencia porque no se hacen copias*/
    return titulo;
}

const std::string& Libro::getAutor() const {
    return autor;
}

void Libro::mostrarInfo() const {
    std::cout << "\"" << titulo << "\" por " << autor << std::endl;
}
