#include "Estudiante.h"
#include <iostream>
#include <algorithm>

Estudiante::Estudiante(std::string n) 
    : nombre(std::move(n)) {}

void Estudiante::prestarLibro(Libro* libro) {
    if (libro != nullptr) {
        librosPrestados.push_back(libro);
        std::cout << nombre << " tomó prestado: " << libro->getTitulo() << std::endl;
    }
}
/*este metodo recibe un puntero a un libro, si dicho puntero no esta vacío
se agrega al vector de punteros librosPrestados
uso libro->getTitulo() porque estoy trabajando con punteros*/

void Estudiante::devolverLibro(Libro* libro) {
    auto it = std::find(librosPrestados.begin(), librosPrestados.end(), libro);
    if (it != librosPrestados.end()) {
        librosPrestados.erase(it);
        std::cout << nombre << " devolvió: " << libro->getTitulo() << std::endl;
    }
}

void Estudiante::mostrarLibrosPrestados() const {
    std::cout << "\n" << nombre << " tiene prestados:" << std::endl;
    if (librosPrestados.empty()) {
        std::cout << "  (ningún libro)" << std::endl;
    } else {
        for (const auto* libro : librosPrestados) {/*aca se recorren los punteros y la variable libro apunta al libro actual*/
            std::cout << "  - ";
            libro->mostrarInfo();
        }
    }
}

const std::string& Estudiante::getNombre() const {
    return nombre;
}