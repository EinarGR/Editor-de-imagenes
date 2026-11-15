#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>

class Imagen {
private:
    int** pixeles;
    int alto;
    int ancho;
    int maxVal;

    int saturar(int valor) const;
    void asignarMemoria(int h, int w);
    void liberarMemoria();

public:
    // Constructores y Regla de Tres
    Imagen();
    Imagen(int alto, int ancho, int maxVal = 255);
    Imagen(const Imagen& otra);
    Imagen& operator=(const Imagen& otra);
    ~Imagen();

    // Getters
    int getAlto() const;
    int getAncho() const;
    int getMaxVal() const;

    // Acceso a pixeles con validacion de rango
    int& operator()(int fila, int columna); //asignación del nivel de brillo
    int operator()(int fila, int columna) const; //devuelve copia del nivel de brillo

    // Sobrecarga de operadores aritmeticos y puntuales (con saturacion)
    Imagen operator+(int brillo) const;
    Imagen operator-(int brillo) const;
    Imagen operator-(const Imagen& otra) const;   // Diferencia absoluta
    Imagen operator*(double contraste) const;
    Imagen operator~() const;                     // Negativo

    // Operadores conmutativos (escalar a la izquierda)
    friend Imagen operator+(int brillo, const Imagen& img);
    friend Imagen operator*(double contraste, const Imagen& img);

    // Sobrecarga de operadores relacionales (pixel a pixel)
    bool operator==(const Imagen& otra) const;
    bool operator!=(const Imagen& otra) const;

    // Funciones amigas para entrada/salida en formato PGM (P2)
    friend std::ostream& operator<<(std::ostream& os, const Imagen& img);
    friend std::istream& operator>>(std::istream& is, Imagen& img);
};

#endif