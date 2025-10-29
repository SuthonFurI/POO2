#ifndef PIEZA_H
#define PIEZA_H

#include <string>

class Pieza {
private:
    int id;                       // mejor private para encapsular
public:
    Pieza(int id_);
    virtual ~Pieza() = default;   // destructor virtual por defecto (importante)
    int getId() const;            // acceso al id para quien lo necesite

    // métodos obligatorios para las subclases (polimorfismo)
    virtual double getSuperficie() const = 0;
    virtual std::string descripcion() const = 0;
};

class Rectangular : public Pieza {
    double ancho, alto;
public:
    Rectangular(int id_, double ancho_, double alto_);
    double getSuperficie() const override;
    std::string descripcion() const override;
};

class Circular : public Pieza {
    double radio;
public:
    Circular(int id_, double radio_);
    double getSuperficie() const override;
    std::string descripcion() const override;
};

class TriangularEquilatera : public Pieza {
    double lado;
public:
    TriangularEquilatera(int id_, double lado_);
    double getSuperficie() const override;
    std::string descripcion() const override;
};

#endif