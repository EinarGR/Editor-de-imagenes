#include "Imagen.h"
#include <stdexcept>
#include <cmath>
#include <string>

int Imagen::saturar(int valor) const {
    if (valor < 0) {
        return 0;
    }
    if (valor > maxVal) {
        return maxVal;
    }
    return valor;
}

void Imagen::asignarMemoria(int h, int w) {
    alto = h;
    ancho = w;
    pixeles = new int*[alto];
    for (int i = 0; i < alto; ++i) {
        pixeles[i] = new int[ancho]();
    }
}

void Imagen::liberarMemoria() {
    if (pixeles != nullptr) {
        for (int i = 0; i < alto; ++i) {
            delete[] pixeles[i];
        }
        delete[] pixeles;
        pixeles = nullptr;
    }
}

// Constructor por defecto
Imagen::Imagen() : pixeles(nullptr), alto(1), ancho(1), maxVal(255) {
    asignarMemoria(1, 1);
}

// Constructor parametrizado
Imagen::Imagen(int alto, int ancho, int maxVal) : pixeles(nullptr), alto(0), ancho(0), maxVal(maxVal) {
    if (alto <= 0 || ancho <= 0) {
        throw std::invalid_argument("Las dimensiones de la imagen deben ser mayores a 0");
    }
    if (maxVal <= 0) {
        throw std::invalid_argument("El valor maximo de intensidad debe ser mayor a 0");
    }
    asignarMemoria(alto, ancho);
}

// Constructor de copia profunda
Imagen::Imagen(const Imagen& otra) : pixeles(nullptr), alto(0), ancho(0), maxVal(otra.maxVal) {
    asignarMemoria(otra.alto, otra.ancho);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            pixeles[i][j] = otra.pixeles[i][j];
        }
    }
}

// Operador de asignacion (copia profunda segura)
Imagen& Imagen::operator=(const Imagen& otra) {
    if (this == &otra) {
        return *this;
    }
    liberarMemoria();
    maxVal = otra.maxVal;
    asignarMemoria(otra.alto, otra.ancho);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            pixeles[i][j] = otra.pixeles[i][j];
        }
    }
    return *this;
}

// Destructor
Imagen::~Imagen() {
    liberarMemoria();
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

// Brillo (+)
Imagen Imagen::operator+(int brillo) const {
    Imagen resultado(alto, ancho, maxVal);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            resultado.pixeles[i][j] = saturar(pixeles[i][j] + brillo);
        }
    }
    return resultado;
}

// Brillo (-)
Imagen Imagen::operator-(int brillo) const {
    Imagen resultado(alto, ancho, maxVal);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            resultado.pixeles[i][j] = saturar(pixeles[i][j] - brillo);
        }
    }
    return resultado;
}

// Diferencia absoluta entre dos imagenes
Imagen Imagen::operator-(const Imagen& otra) const {
    if (alto != otra.alto || ancho != otra.ancho) {
        throw std::invalid_argument("Dimensiones incompatibles para restar imagenes");
    }
    int nuevoMax = (maxVal > otra.maxVal) ? maxVal : otra.maxVal;
    Imagen resultado(alto, ancho, nuevoMax);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            int diff = std::abs(pixeles[i][j] - otra.pixeles[i][j]);
            resultado.pixeles[i][j] = resultado.saturar(diff);
        }
    }
    return resultado;
}

// Contraste (*)
Imagen Imagen::operator*(double contraste) const {
    Imagen resultado(alto, ancho, maxVal);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            int val = static_cast<int>(std::round(pixeles[i][j] * contraste));
            resultado.pixeles[i][j] = saturar(val);
        }
    }
    return resultado;
}

// Negativo (~)
Imagen Imagen::operator~() const {
    Imagen resultado(alto, ancho, maxVal);
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            resultado.pixeles[i][j] = saturar(maxVal - pixeles[i][j]);
        }
    }
    return resultado;
}

Imagen operator+(int brillo, const Imagen& img) {
    return img + brillo;
}

Imagen operator*(double contraste, const Imagen& img) {
    return img * contraste;
}

// Comparacion pixel a pixel (==)
bool Imagen::operator==(const Imagen& otra) const {
    if (alto != otra.alto || ancho != otra.ancho || maxVal != otra.maxVal) {
        return false;
    }
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            if (pixeles[i][j] != otra.pixeles[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Desigualdad (!=)
bool Imagen::operator!=(const Imagen& otra) const {
    return !(*this == otra);
}

// Volcar imagen en formato PGM texto (P2)
std::ostream& operator<<(std::ostream& os, const Imagen& img) {
    os << "P2\n";
    os << img.ancho << " " << img.alto << "\n";
    os << img.maxVal << "\n";
    for (int i = 0; i < img.alto; ++i) {
        for (int j = 0; j < img.ancho; ++j) {
            os << img.pixeles[i][j];
            if (j + 1 < img.ancho) {
                os << " ";
            }
        }
        os << "\n";
    }
    return os;
}

// Funcion auxiliar interna para leer tokens ignorando comentarios '#' en PGM
namespace {
    bool leerTokenPGM(std::istream& is, std::string& token) {
        while (is >> token) {
            if (!token.empty() && token[0] == '#') {
                std::string resto;
                std::getline(is, resto);
                continue;
            }
            return true;
        }
        return false;
    }
}

// Leer imagen en formato PGM texto (P2)
std::istream& operator>>(std::istream& is, Imagen& img) {
    std::string firma;
    if (!leerTokenPGM(is, firma) || firma != "P2") {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::string tokAncho, tokAlto, tokMax;
    if (!leerTokenPGM(is, tokAncho) || !leerTokenPGM(is, tokAlto) || !leerTokenPGM(is, tokMax)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    int nuevoAncho = 0, nuevoAlto = 0, nuevoMax = 0;
    try {
        nuevoAncho = std::stoi(tokAncho);
        nuevoAlto = std::stoi(tokAlto);
        nuevoMax = std::stoi(tokMax);
    } catch (...) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (nuevoAncho <= 0 || nuevoAlto <= 0 || nuevoMax <= 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    Imagen temporal(nuevoAlto, nuevoAncho, nuevoMax);
    for (int i = 0; i < nuevoAlto; ++i) {
        for (int j = 0; j < nuevoAncho; ++j) {
            std::string tokPixel;
            if (!leerTokenPGM(is, tokPixel)) {
                is.setstate(std::ios::failbit);
                return is;
            }
            try {
                int val = std::stoi(tokPixel);
                temporal.pixeles[i][j] = temporal.saturar(val);
            } catch (...) {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
    }

    img = temporal;
    return is;
}