#include "Filtro.h"

Filtro::Filtro(const std::string& nombreFiltro) {
    this->nombreFiltro = nombreFiltro;
}

Filtro::~Filtro() {}

std::string Filtro::nombre() const {
    return nombreFiltro;
}

int Filtro::saturar(int valor, int maxVal) const {
    if (valor < 0) {
        return 0;
    }
    if (valor > maxVal) {
        return maxVal;
    }
    return valor;
}
