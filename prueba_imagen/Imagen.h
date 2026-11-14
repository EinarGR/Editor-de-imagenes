#ifndef IMAGEN_H
#define IMAGEN_H

// Version minima SOLO para probar los filtros. Se reemplaza por la Imagen del Integrante 1.
class Imagen {
private:
    int** pixeles;
    int alto;
    int ancho;
    int maxVal;

public:
    Imagen(int alto, int ancho, int maxVal);
    Imagen(const Imagen& otra);
    Imagen& operator=(const Imagen& otra);
    ~Imagen();

    int getAlto() const;
    int getAncho() const;
    int getMaxVal() const;
    int& operator()(int fila, int columna);
    int operator()(int fila, int columna) const;
};

#endif
