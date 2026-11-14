#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>
#include "Imagen.h"
#include "Filtro.h"
#include "Bitacora.h"
#include "ArchivoPGM.h"

class Editor {
private:
    Imagen imagen;                    // COMPOSICION: la imagen nace y muere con el editor
    bool hayImagen;
    std::string rutaActual;
    std::vector<Imagen> historial;    // copias profundas para deshacer
    std::vector<Filtro*> filtros;     // AGREGACION: el editor NO crea ni borra los filtros
    Bitacora bitacora;
    std::string error;

    static const int MAX_DESHACER = 20;

public:
    Editor();

    void registrarFiltro(Filtro* filtro);
    int getCantidadFiltros() const;
    std::string nombreFiltro(int indice) const;   // "" si el indice no existe

    bool tieneImagen() const;
    const Imagen& getImagen() const;              // usar solo si tieneImagen()
    std::string getRutaActual() const;
    std::string getError() const;                 // motivo del ultimo fallo

    bool cargar(const std::string& ruta);
    bool guardar(const std::string& ruta, int formato);   // formato: 2 = P2, 5 = P5

    bool aplicarFiltro(int indice);
    bool deshacer();
    int getCantidadDeshacer() const;

    Bitacora& getBitacora();
};

#endif
