#ifndef FILTRO_H
#define FILTRO_H

#include <string>
#include "Imagen.h"

class Filtro {
protected:
    std::string nombreFiltro;

    int saturar(int valor, int maxVal) const;

public:
    Filtro(const std::string& nombreFiltro);
    virtual ~Filtro();

    std::string nombre() const;
    virtual Imagen aplicar(const Imagen& img) const = 0;
};

#endif
