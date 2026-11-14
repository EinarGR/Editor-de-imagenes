#ifndef ESPEJOHORIZONTAL_H
#define ESPEJOHORIZONTAL_H

#include "Filtro.h"

class EspejoHorizontal : public Filtro {
public:
    EspejoHorizontal();

    Imagen aplicar(const Imagen& img) const override;
};

#endif
