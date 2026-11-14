#include "Sobel.h"
#include <cmath>

Sobel::Sobel() : Filtro("Sobel") {
    int x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gx.setValor(i, j, x[i][j]);
            gy.setValor(i, j, y[i][j]);
        }
    }
}

// Magnitud del gradiente: valores altos donde hay un cambio brusco (borde).
Imagen Sobel::aplicar(const Imagen& img) const {
    Imagen resultado(img.getAlto(), img.getAncho(), img.getMaxVal());
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            double dx = gx.aplicarEn(img, i, j);
            double dy = gy.aplicarEn(img, i, j);
            int magnitud = (int)(std::sqrt(dx * dx + dy * dy) + 0.5);
            resultado(i, j) = saturar(magnitud, img.getMaxVal());
        }
    }
    return resultado;
}
