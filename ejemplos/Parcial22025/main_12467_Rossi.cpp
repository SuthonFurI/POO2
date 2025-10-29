#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "chapa.h"
#include "pieza.h"

int main() {
    Chapa& chapa = Chapa::getInstancia(1000, 2000, 3); // parámetros iniciales
    std::vector<std::unique_ptr<Pieza>> piezas;
    int nextId = 1;

    auto clearInput = []() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    };

    while (true) {
        std::cout << "Agregar pieza? (s/n): ";
        char c;
        if (!(std::cin >> c)) {
            clearInput();
            continue;
        }
        if (c != 's' && c != 'S') break;

        std::cout << "Tipo (r=rectangulo, c=circulo, t=triangulo): ";
        char tipo;
        if (!(std::cin >> tipo)) {
            clearInput();
            continue;
        }

        if (tipo == 'r') {
            while (true) {
                double w, h;
                std::cout << "Ancho y alto: ";
                if (!(std::cin >> w >> h)) { clearInput(); std::cout << "Entrada inválida. Intentá de nuevo.\n"; continue; }
                try {
                    auto p = std::make_unique<Rectangular>(nextId, w, h);
                    double area = p->getSuperficie();
                    piezas.push_back(std::move(p));
                    chapa.ocupar(area);
                    std::cout << "Pieza ID " << nextId << " area=" << area << "\n";
                    ++nextId;
                    break;
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: " << e.what() << " Reingresá las dimensiones.\n";
                }
            }
        } else if (tipo == 'c') {
            while (true) {
                double r;
                std::cout << "Radio: ";
                if (!(std::cin >> r)) { clearInput(); std::cout << "Entrada inválida. Intentá de nuevo.\n"; continue; }
                try {
                    auto p = std::make_unique<Circular>(nextId, r);
                    double area = p->getSuperficie();
                    piezas.push_back(std::move(p));
                    chapa.ocupar(area);
                    std::cout << "Pieza ID " << nextId << " area=" << area << "\n";
                    ++nextId;
                    break;
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: " << e.what() << " Reingresá las dimensiones.\n";
                }
            }
        } else if (tipo == 't') {
            while (true) {
                double a;
                std::cout << "Lado: ";
                if (!(std::cin >> a)) { clearInput(); std::cout << "Entrada inválida. Intentá de nuevo.\n"; continue; }
                try {
                    auto p = std::make_unique<TriangularEquilatera>(nextId, a);
                    double area = p->getSuperficie();
                    piezas.push_back(std::move(p));
                    chapa.ocupar(area);
                    std::cout << "Pieza ID " << nextId << " area=" << area << "\n";
                    ++nextId;
                    break;
                } catch (const std::invalid_argument& e) {
                    std::cout << "Error: " << e.what() << " Reingresá las dimensiones.\n";
                }
            }
        } else {
            std::cout << "Tipo inválido.\n";
            continue;
        }

        std::cout << "Ocupacion actual: " << chapa.getPorcentajeOcupacion() << "%\n";
        if (chapa.getPorcentajeOcupacion() > 75.0) {
            std::cout << "Supera 75%: finalizando ingreso.\n";
            break;
        }
    }

    // Reporte final
    std::cout << "REPORTE\n";
    std::cout << "ID\tTipo y dimensiones\tArea\n";
    for (const auto& p : piezas) {
        std::cout << p->getId() << "\t" << p->descripcion() << "\t" << p->getSuperficie() << "\n";
    }
    std::cout << "Cantidad piezas: " << piezas.size() << "\n";
    std::cout << "Superficie ocupada: " << chapa.getAreaOcupada() << "\n";
    std::cout << "Porcentaje disponible: " << (100.0 - chapa.getPorcentajeOcupacion()) << "%\n";

    return 0;
}