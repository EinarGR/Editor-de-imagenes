#include "Bitacora.h"
#include <fstream>

using namespace std;

void Bitacora::agregar(const string& texto) {
    string limpio = texto;
    for (int i = 0; i < (int)limpio.size(); i++) {
        if (limpio[i] == '\n' || limpio[i] == '\r') {
            limpio[i] = ' ';
        }
    }
    entradas.push_back(limpio);
}

int Bitacora::getCantidad() const { return (int)entradas.size(); }

string Bitacora::getEntrada(int i) const {
    if (i < 0 || i >= (int)entradas.size()) {
        return "";
    }
    return entradas[i];
}

string Bitacora::getError() const { return error; }

void Bitacora::limpiar() { entradas.clear(); }

void Bitacora::listar(ostream& os) const {
    if (entradas.empty()) {
        os << "La bitacora esta vacia" << endl;
    }
    for (int i = 0; i < (int)entradas.size(); i++) {
        os << i + 1 << ". " << entradas[i] << endl;
    }
}

bool Bitacora::guardar(const string& ruta) {
    error = "";
    ofstream f(ruta);
    if (!f) {
        error = "No se pudo crear la bitacora: " + ruta;
        return false;
    }
    f << "BITACORA v1" << "\n";
    for (int i = 0; i < (int)entradas.size(); i++) {
        f << entradas[i] << "\n";
    }
    f.flush();
    if (!f) {
        error = "Error al escribir la bitacora: " + ruta;
        return false;
    }
    return true;
}

bool Bitacora::cargar(const string& ruta) {
    error = "";
    ifstream f(ruta);
    if (!f) {
        error = "No se pudo abrir la bitacora: " + ruta;
        return false;
    }
    string linea;
    if (!getline(f, linea) || linea != "BITACORA v1") {
        error = "Archivo de bitacora invalido: " + ruta;
        return false;
    }
    vector<string> nuevas;
    while (getline(f, linea)) {
        if (!linea.empty() && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (!linea.empty()) {
            nuevas.push_back(linea);
        }
    }
    entradas = nuevas;
    return true;
}
