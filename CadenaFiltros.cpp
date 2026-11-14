#include "CadenaFiltros.h"
#include <iostream>

using namespace std;

void CadenaFiltros::agregar(Filtro* filtro) {
    if (filtro != nullptr) {
        filtros.push_back(filtro);
    }
}

void CadenaFiltros::quitarUltimo() {
    if (!filtros.empty()) {
        filtros.pop_back();
    }
}

void CadenaFiltros::limpiar() {
    filtros.clear();
}

int CadenaFiltros::getCantidad() const {
    return (int)filtros.size();
}

void CadenaFiltros::listar() const {
    if (filtros.empty()) {
        cout << "La cadena esta vacia" << endl;
    }
    for (int i = 0; i < (int)filtros.size(); i++) {
        cout << i + 1 << ") " << filtros[i]->nombre() << endl;
    }
}

// Polimorfismo: cada puntero llama al aplicar() de su clase concreta, sin if ni switch.
Imagen CadenaFiltros::aplicar(const Imagen& img) const {
    Imagen resultado = img;
    for (int i = 0; i < (int)filtros.size(); i++) {
        resultado = filtros[i]->aplicar(resultado);
    }
    return resultado;
}
