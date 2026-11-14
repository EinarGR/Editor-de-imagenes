#ifndef UMBRAL_H
#define UMBRAL_H

#include "Filtro.h"

class Umbral : public Filtro {
private:
    int umbral;

public:
    Umbral(int umbral);

    int getUmbral() const;
    void setUmbral(int umbral);

    Imagen aplicar(const Imagen& img) const override;
};

#endif
