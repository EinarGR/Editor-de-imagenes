#ifndef CADENAFILTROS_H
#define CADENAFILTROS_H

#include <vector>
#include "Filtro.h"

class CadenaFiltros {
private:
    std::vector<Filtro*> filtros;   // agregacion: la cadena no crea ni borra los filtros

public:
    void agregar(Filtro* filtro);
    void quitarUltimo();
    void limpiar();
    int getCantidad() const;
    void listar() const;
    Imagen aplicar(const Imagen& img) const;
};

#endif
