#include "Rotar90.h"

Rotar90::Rotar90() : Filtro("Rotar 90") {}

// Giro horario: el alto y el ancho se intercambian y (i, j) pasa a (j, alto - 1 - i).
Imagen Rotar90::aplicar(const Imagen& img) const {
    Imagen resultado(img.getAncho(), img.getAlto(), img.getMaxVal());
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            resultado(j, img.getAlto() - 1 - i) = img(i, j);
        }
    }
    return resultado;
}
