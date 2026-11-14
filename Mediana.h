#ifndef MEDIANA_H
#define MEDIANA_H

#include "Filtro.h"

class Mediana : public Filtro {
private:
    void ordenar(int valores[], int n) const;

public:
    Mediana();

    Imagen aplicar(const Imagen& img) const override;
};

#endif
