#include "chapa.h"

// Constructor privado por defecto (puede seguir existiendo)
Chapa::Chapa() : ancho(1000), largo(2000), espesor(3), areaOcupada(0.0) { }

// Constructor privado parametrizado
Chapa::Chapa(int ancho_, int largo_, int espesor_)
    : ancho(ancho_), largo(largo_), espesor(espesor_), areaOcupada(0.0) { }

// getInstancia parametrizable: la primera llamada crea la instancia con los valores dados
Chapa& Chapa::getInstancia(int ancho, int largo, int espesor) {
    static Chapa* instancia = nullptr;
    if (!instancia) {
        instancia = new Chapa(ancho, largo, espesor);
        // nota: se usa new para poder pasar parámetros; la instancia duerme hasta el fin del programa
    }
    return *instancia;
}

// Implementación de getSuperficie
double Chapa::getSuperficie() const {
    return static_cast<double>(ancho) * static_cast<double>(largo);  // Superficie = ancho × largo
}

double Chapa::getAreaOcupada() const {
    return areaOcupada;
}

double Chapa::getPorcentajeOcupacion() const {
    double total = getSuperficie();
    if (total <= 0.0) return 0.0;
    return (areaOcupada / total) * 100.0;
}

void Chapa::ocupar(double area) {
    if (area > 0.0) areaOcupada += area;
}