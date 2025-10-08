#ifndef ARCHIVO_318_H
#define ARCHIVO_318_H

#include <string>
#include <fstream>
#include <filesystem>

class Archivo_318 {
private:
    std::string name;       // Nombre del archivo
    std::string datetime;   // Fecha de última modificación
    std::string owner;      // Propietario (simulado)
    std::size_t dimension;  // Tamaño en bytes
    std::fstream file;      // Stream de archivo

public:
    // Constructor
    Archivo_318(const std::string& nombre);

    // Métodos principales
    bool open(std::ios::openmode mode);
    void close();
    bool write(const std::string& data);
    bool exists() const;
    std::string getLine();
    std::string getInfo() const;

    // Getters
    std::string getName() const;
    std::string getOwner() const;
    std::string getDatetime() const;
    std::size_t getDimension() const;
};

#endif

