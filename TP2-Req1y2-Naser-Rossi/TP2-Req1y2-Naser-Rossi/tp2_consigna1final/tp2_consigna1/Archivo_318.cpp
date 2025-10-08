#include "Archivo_318.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

Archivo_318::Archivo_318(const std::string& nombre) : name(nombre) {
    if (std::filesystem::exists(nombre)) {
        dimension = std::filesystem::file_size(nombre);
        owner = "Rossi-Naser";  

        auto ftime = std::filesystem::last_write_time(nombre);
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now()
        );

        std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
        datetime = std::string(std::asctime(std::localtime(&cftime)));
    }
}

bool Archivo_318::open(std::ios::openmode mode) {
    file.open(name, mode);
    return file.is_open();
}

void Archivo_318::close() {
    if (file.is_open()) {
        file.close();
    }
}

bool Archivo_318::write(const std::string& data) {
    if (!file.is_open()) return false;
    file << data;
    return true;
}

bool Archivo_318::exists() const {
    return std::filesystem::exists(name);
}

std::string Archivo_318::getLine() {
    std::string line;
    if (file.is_open()) {
        std::getline(file, line);
    }
    return line;
}

std::string Archivo_318::getInfo() const {
    std::string info = "Archivo: " + name + "\n";
    info += "Propietario: " + owner + "\n";
    info += "Fecha mod: " + datetime;
    info += "Dimension: " + std::to_string(dimension) + " bytes\n";
    return info;
}

std::string Archivo_318::getName() const { return name; }
std::string Archivo_318::getOwner() const { return owner; }
std::string Archivo_318::getDatetime() const { return datetime; }
std::size_t Archivo_318::getDimension() const { return dimension; }
