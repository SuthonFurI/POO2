#ifndef CHAPA_H
#define CHAPA_H

class Chapa {
private:
    int ancho;
    int largo;
    int espesor;
    double areaOcupada;

    Chapa();                     // <-- conservar constructor por defecto si querés
    Chapa(int ancho_, int largo_, int espesor_); // nuevo: constructor parametrizado (privado)
    //tengo 2 constructores privados si quiero que los parametros vengan del usuario
    public:
    // ahora acepta parámetros (tienen valores por defecto)
    static Chapa& getInstancia(int ancho = 1000, int largo = 2000, int espesor = 3);

    // getters
    double getSuperficie() const;
    double getAreaOcupada() const;
    double getPorcentajeOcupacion() const;

    void ocupar(double area);

    Chapa(const Chapa&) = delete;
    Chapa& operator=(const Chapa&) = delete;
};

#endif