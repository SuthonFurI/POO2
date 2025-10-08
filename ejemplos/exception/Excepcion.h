#ifndef EXCEPCION_H
#define EXCEPCION_H

#include <stdexcept>
#include <string>

/* std::runtime_error es la clase base para las excepciones en tiempo de ejecución
viene de la librería estándar <stdexcept> y hereda de std::exception */
   
class ValidacionError : public std::runtime_error {
public:
    explicit ValidacionError(const std::string& msg) /*uso explicit porque un char puede
    activar el error, con explicit si o si debe recibir una string*/
        : std::runtime_error(msg) {}
};

#endif
