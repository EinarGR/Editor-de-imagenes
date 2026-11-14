#include "ArchivoPGM.h"
#include <vector>
#include <cctype>

using namespace std;

ArchivoPGM::ArchivoPGM(const string& ruta) {
    this->ruta = ruta;
    formato = 2;
    error = "";
}

string ArchivoPGM::getRuta() const { return ruta; }
int ArchivoPGM::getFormato() const { return formato; }
string ArchivoPGM::getError() const { return error; }

string ArchivoPGM::getNombreFormato() const {
    if (formato == 5) {
        return "P5";
    }
    return "P2";
}

bool ArchivoPGM::fallar(const string& mensaje) {
    error = mensaje;
    return false;
}

// Lee el siguiente token saltando espacios y comentarios (# hasta fin de linea).
// No consume el separador que lo termina (importa para P5).
bool ArchivoPGM::leerToken(istream& f, string& token) {
    token = "";
    int c = f.peek();
    while (c != EOF) {
        if (isspace(c)) {
            f.get();
        } else if (c == '#') {
            c = f.get();
            while (c != EOF && c != '\n') {
                c = f.get();
            }
        } else {
            break;
        }
        c = f.peek();
    }
    c = f.peek();
    while (c != EOF && !isspace(c) && c != '#') {
        token.push_back((char)f.get());
        c = f.peek();
    }
    return token.size() > 0;
}

bool ArchivoPGM::leerEntero(istream& f, const string& que, int& valor) {
    string token;
    if (!leerToken(f, token)) {
        return fallar("Archivo incompleto: falta " + que);
    }
    if (token.size() > 9) {
        return fallar("Valor invalido para " + que + ": " + token);
    }
    for (int i = 0; i < (int)token.size(); i++) {
        if (!isdigit((unsigned char)token[i])) {
            return fallar("Valor no numerico para " + que + ": " + token);
        }
    }
    valor = 0;
    for (int i = 0; i < (int)token.size(); i++) {
        valor = valor * 10 + (token[i] - '0');
    }
    return true;
}

// Solo modifica 'destino' si la lectura completa tuvo exito.
bool ArchivoPGM::leer(Imagen& destino) {
    error = "";
    ifstream f(ruta, ios::binary);
    if (!f) {
        return fallar("No se pudo abrir el archivo: " + ruta);
    }

    string magia;
    if (!leerToken(f, magia)) {
        return fallar("Archivo vacio: " + ruta);
    }
    int nuevoFormato;
    if (magia == "P2") {
        nuevoFormato = 2;
    } else if (magia == "P5") {
        nuevoFormato = 5;
    } else {
        return fallar("Formato no soportado (se esperaba P2 o P5): " + magia);
    }

    int ancho, alto, maxVal;
    if (!leerEntero(f, "el ancho", ancho) || !leerEntero(f, "el alto", alto) ||
        !leerEntero(f, "el valor maximo", maxVal)) {
        return false;
    }
    if (ancho <= 0 || alto <= 0) {
        return fallar("Dimensiones invalidas en " + ruta);
    }
    if (maxVal < 1 || maxVal > 65535) {
        return fallar("Valor maximo fuera de rango (1-65535)");
    }

    Imagen temporal(alto, ancho, maxVal);
    if (nuevoFormato == 2) {
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                int v;
                if (!leerEntero(f, "un pixel", v)) {
                    return false;
                }
                if (v > maxVal) {
                    return fallar("Pixel mayor que el valor maximo");
                }
                temporal(i, j) = v;
            }
        }
    } else {
        f.get();   // un unico separador despues del valor maximo
        int bytes = 1;
        if (maxVal > 255) {
            bytes = 2;
        }
        vector<char> fila(ancho * bytes);
        for (int i = 0; i < alto; i++) {
            f.read(&fila[0], (streamsize)fila.size());
            if ((int)f.gcount() != (int)fila.size()) {
                return fallar("Datos binarios incompletos en " + ruta);
            }
            for (int j = 0; j < ancho; j++) {
                int v;
                if (bytes == 1) {
                    v = (unsigned char)fila[j];
                } else {
                    v = (unsigned char)fila[2 * j] * 256 + (unsigned char)fila[2 * j + 1];
                }
                if (v > maxVal) {
                    return fallar("Pixel mayor que el valor maximo");
                }
                temporal(i, j) = v;
            }
        }
    }
    destino = temporal;
    formato = nuevoFormato;
    return true;
}

bool ArchivoPGM::escribir(const Imagen& img, int nuevoFormato) {
    error = "";
    if (nuevoFormato != 2 && nuevoFormato != 5) {
        return fallar("Formato de salida invalido");
    }
    ofstream f(ruta, ios::binary);
    if (!f) {
        return fallar("No se pudo crear el archivo: " + ruta);
    }
    int alto = img.getAlto();
    int ancho = img.getAncho();
    int maxVal = img.getMaxVal();

    f << "P" << nuevoFormato << "\n";
    f << "# Generado por el Editor de imagenes\n";
    f << ancho << " " << alto << "\n" << maxVal << "\n";

    if (nuevoFormato == 2) {
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                f << img(i, j);
                if (j + 1 < ancho) {
                    f << " ";
                } else {
                    f << "\n";
                }
            }
        }
    } else {
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                int v = img(i, j);
                if (maxVal > 255) {
                    f.put((char)(v / 256));
                }
                f.put((char)(v % 256));
            }
        }
    }
    f.flush();
    if (!f) {
        return fallar("Error al escribir el archivo: " + ruta);
    }
    formato = nuevoFormato;
    return true;
}
