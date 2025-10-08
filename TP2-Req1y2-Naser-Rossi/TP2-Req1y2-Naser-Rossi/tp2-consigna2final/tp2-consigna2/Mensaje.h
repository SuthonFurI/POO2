#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include <map>
#include <variant>
#include <fstream>
#include <sstream>
#include <iostream>

// Alias para tipos de datos soportados
using Valor = std::variant<int, double, std::string>;

class Mensaje {
protected:
    int codigoOperacion;
    std::map<std::string, Valor> datos;

private:
    // Helper estático para la deserialización: infiere el tipo (int, double, o string)
    static Valor parseValor(const std::string& str);

public:
    Mensaje(int codigo = 0);

    void setCodigoOperacion(int codigo);
    int getCodigoOperacion() const;

    void agregarDato(const std::string& clave, const Valor& valor);
    Valor obtenerDato(const std::string& clave) const;

    // Métodos virtuales para serialización/deserialización (base para polimorfismo)
    virtual std::string serializar() const;
    virtual bool deserializar(const std::string& data);

    // Métodos virtuales para persistencia (lógica centralizada)
    virtual bool guardarEnArchivo(const std::string& nombreArchivo) const;
    virtual bool cargarDesdeArchivo(const std::string& nombreArchivo);

    virtual ~Mensaje();
};

#endif

