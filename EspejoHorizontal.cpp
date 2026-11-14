#include "EspejoHorizontal.h"

EspejoHorizontal::EspejoHorizontal() : Filtro("Espejo horizontal") {}

// La columna j pasa a la posicion (ancho - 1 - j).
Imagen EspejoHorizontal::aplicar(const Imagen& img) const {
    Imagen resultado(img.getAlto(), img.getAncho(), img.getMaxVal());
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            resultado(i, img.getAncho() - 1 - j) = img(i, j);
        }
    }
    return resultado;
}
