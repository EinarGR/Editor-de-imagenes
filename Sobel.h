#ifndef SOBEL_H
#define SOBEL_H

#include "Filtro.h"
#include "Kernel.h"

class Sobel : public Filtro {
private:
    Kernel<3> gx;
    Kernel<3> gy;

public:
    Sobel();

    Imagen aplicar(const Imagen& img) const override;
};

#endif
