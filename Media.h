#ifndef MEDIA_H
#define MEDIA_H

#include "Filtro.h"
#include "Kernel.h"

class Media : public Filtro {
private:
    Kernel<3> mascara;

public:
    Media();

    Imagen aplicar(const Imagen& img) const override;
};

#endif
