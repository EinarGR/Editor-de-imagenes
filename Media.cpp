#include "Media.h"

Media::Media() : Filtro("Media") {
    mascara.llenar(1);
    mascara.setDivisor(9);
}

// Cada pixel pasa a ser el promedio de su vecindad 3x3.
Imagen Media::aplicar(const Imagen& img) const {
    Imagen resultado(img.getAlto(), img.getAncho(), img.getMaxVal());
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            int valor = (int)(mascara.aplicarEn(img, i, j) + 0.5);
            resultado(i, j) = saturar(valor, img.getMaxVal());
        }
    }
    return resultado;
}
