#include "Editor.h"

using namespace std;

Editor::Editor() : imagen(1, 1, 255) {
    hayImagen = false;
    rutaActual = "";
    error = "";
}

void Editor::registrarFiltro(Filtro* filtro) {
    if (filtro != nullptr) {
        filtros.push_back(filtro);
    }
}

int Editor::getCantidadFiltros() const { return (int)filtros.size(); }

string Editor::nombreFiltro(int indice) const {
    if (indice < 0 || indice >= (int)filtros.size()) {
        return "";
    }
    return filtros[indice]->nombre();
}

bool Editor::tieneImagen() const { return hayImagen; }
const Imagen& Editor::getImagen() const { return imagen; }
string Editor::getRutaActual() const { return rutaActual; }
string Editor::getError() const { return error; }

bool Editor::cargar(const string& ruta) {
    error = "";
    ArchivoPGM archivo(ruta);
    Imagen nueva(1, 1, 255);
    if (!archivo.leer(nueva)) {      // si falla, el editor queda intacto
        error = archivo.getError();
        return false;
    }
    imagen = nueva;
    hayImagen = true;
    rutaActual = ruta;
    historial.clear();
    bitacora.agregar("Cargada " + ruta + " (" + to_string(imagen.getAncho()) + "x" +
                     to_string(imagen.getAlto()) + ", " + archivo.getNombreFormato() + ")");
    return true;
}

bool Editor::guardar(const string& ruta, int formato) {
    error = "";
    if (!hayImagen) {
        error = "No hay imagen para guardar";
        return false;
    }
    ArchivoPGM archivo(ruta);
    if (!archivo.escribir(imagen, formato)) {
        error = archivo.getError();
        return false;
    }
    bitacora.agregar("Guardada " + ruta + " (" + archivo.getNombreFormato() + ")");
    return true;
}

// Polimorfismo: se llama a aplicar() por puntero a la base, sin if ni switch sobre el tipo.
bool Editor::aplicarFiltro(int indice) {
    error = "";
    if (!hayImagen) {
        error = "No hay imagen cargada";
        return false;
    }
    if (indice < 0 || indice >= (int)filtros.size()) {
        error = "Filtro inexistente";
        return false;
    }
    Imagen resultado = filtros[indice]->aplicar(imagen);
    historial.push_back(imagen);
    if ((int)historial.size() > MAX_DESHACER) {
        historial.erase(historial.begin());
    }
    imagen = resultado;
    bitacora.agregar("Filtro " + filtros[indice]->nombre() + " -> " +
                     to_string(imagen.getAncho()) + "x" + to_string(imagen.getAlto()));
    return true;
}

bool Editor::deshacer() {
    error = "";
    if (!hayImagen || historial.empty()) {
        error = "No hay operaciones para deshacer";
        return false;
    }
    imagen = historial.back();
    historial.pop_back();
    bitacora.agregar("Deshacer -> " + to_string(imagen.getAncho()) + "x" +
                     to_string(imagen.getAlto()));
    return true;
}

int Editor::getCantidadDeshacer() const { return (int)historial.size(); }

Bitacora& Editor::getBitacora() { return bitacora; }
