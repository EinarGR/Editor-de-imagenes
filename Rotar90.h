#ifndef ROTAR90_H
#define ROTAR90_H

#include "Filtro.h"

class Rotar90 : public Filtro {
public:
    Rotar90();

    Imagen aplicar(const Imagen& img) const override;
};

#endif
