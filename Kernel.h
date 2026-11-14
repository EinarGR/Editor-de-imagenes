#ifndef KERNEL_H
#define KERNEL_H

#include "Imagen.h"

// Mascara de convolucion de tamanio fijo N x N (N impar).
// Al ser plantilla, todo va en el .h para que el compilador genere Kernel<3>, Kernel<5>, etc.
template <int N>
class Kernel {
private:
    int valores[N][N];
    int divisor;

public:
    Kernel() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                valores[i][j] = 0;
            }
        }
        divisor = 1;
    }

    int getTamanio() const { return N; }
    int getValor(int fila, int columna) const { return valores[fila][columna]; }
    int getDivisor() const { return divisor; }

    void setValor(int fila, int columna, int valor) {
        if (fila >= 0 && fila < N && columna >= 0 && columna < N) {
            valores[fila][columna] = valor;
        }
    }

    void setDivisor(int divisor) {
        if (divisor != 0) {
            this->divisor = divisor;
        }
    }

    void llenar(int valor) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                valores[i][j] = valor;
            }
        }
    }

    // Borde: si el vecino cae fuera de la imagen se usa el pixel del borde mas cercano.
    double aplicarEn(const Imagen& img, int fila, int columna) const {
        int radio = N / 2;
        double suma = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int f = fila + i - radio;
                int c = columna + j - radio;
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
                suma = suma + valores[i][j] * img(f, c);
            }
        }
        return suma / divisor;
    }
};

#endif
