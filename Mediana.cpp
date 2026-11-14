#include "Mediana.h"

Mediana::Mediana() : Filtro("Mediana") {}

// Ordenamiento burbuja propio (sin std::sort).
void Mediana::ordenar(int valores[], int n) const {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (valores[j] > valores[j + 1]) {
                int temp = valores[j];
                valores[j] = valores[j + 1];
                valores[j + 1] = temp;
            }
        }
    }
}

// Cada pixel toma el valor central de su vecindad 3x3 ordenada.
Imagen Mediana::aplicar(const Imagen& img) const {
    Imagen resultado(img.getAlto(), img.getAncho(), img.getMaxVal());
    int vecinos[9];
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            int k = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int f = i + di;
                    int c = j + dj;
                    if (f < 0) {
                        f = 0;
                    }
                    if (f >= img.getAlto()) {
                        f = img.getAlto() - 1;
                    }
                    if (c < 0) {
                        c = 0;
                    }
                    if (c >= img.getAncho()) {
                        c = img.getAncho() - 1;
                    }
                    vecinos[k] = img(f, c);
                    k++;
                }
            }
            ordenar(vecinos, 9);
            resultado(i, j) = vecinos[4];
        }
    }
    return resultado;
}
