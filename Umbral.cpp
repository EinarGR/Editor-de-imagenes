#include "Umbral.h"

Umbral::Umbral(int umbral) : Filtro("Umbral") {
    setUmbral(umbral);
}

int Umbral::getUmbral() const { return umbral; }

void Umbral::setUmbral(int umbral) {
    if (umbral < 0) {
        umbral = 0;
    }
    this->umbral = umbral;
}

// Pixeles >= umbral pasan a blanco y el resto a negro.
Imagen Umbral::aplicar(const Imagen& img) const {
    Imagen resultado(img.getAlto(), img.getAncho(), img.getMaxVal());
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            if (img(i, j) >= umbral) {
                resultado(i, j) = img.getMaxVal();
            } else {
                resultado(i, j) = 0;
            }
        }
    }
    return resultado;
}
