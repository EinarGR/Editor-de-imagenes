#include "Imagen.h"
#include <stdexcept>

Imagen::Imagen(int alto, int ancho, int maxVal) {
    this->alto = alto;
    this->ancho = ancho;
    this->maxVal = maxVal;
    pixeles = new int*[alto];
    for (int i = 0; i < alto; i++) {
        pixeles[i] = new int[ancho]();
    }
}

Imagen::Imagen(const Imagen& otra) : Imagen(otra.alto, otra.ancho, otra.maxVal) {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            pixeles[i][j] = otra.pixeles[i][j];
        }
    }
}

Imagen& Imagen::operator=(const Imagen& otra) {
    if (this == &otra) {
        return *this;
    }
    for (int i = 0; i < alto; i++) {
        delete[] pixeles[i];
    }
    delete[] pixeles;
    alto = otra.alto;
    ancho = otra.ancho;
    maxVal = otra.maxVal;
    pixeles = new int*[alto];
    for (int i = 0; i < alto; i++) {
        pixeles[i] = new int[ancho];
        for (int j = 0; j < ancho; j++) {
            pixeles[i][j] = otra.pixeles[i][j];
        }
    }
    return *this;
}

Imagen::~Imagen() {
    for (int i = 0; i < alto; i++) {
        delete[] pixeles[i];
    }
    delete[] pixeles;
}

int Imagen::getAlto() const { return alto; }
int Imagen::getAncho() const { return ancho; }
int Imagen::getMaxVal() const { return maxVal; }

int& Imagen::operator()(int fila, int columna) {
    if (fila < 0 || fila >= alto || columna < 0 || columna >= ancho) {
        throw std::out_of_range("Pixel fuera de rango");
    }
    return pixeles[fila][columna];
}

int Imagen::operator()(int fila, int columna) const {
    if (fila < 0 || fila >= alto || columna < 0 || columna >= ancho) {
        throw std::out_of_range("Pixel fuera de rango");
    }
    return pixeles[fila][columna];
}
