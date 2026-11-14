#ifndef MENU_H
#define MENU_H

#include <string>
#include "Editor.h"
#include "Umbral.h"

// Interfaz de consola. Toda entrada se valida; un dato invalido nunca termina el programa.
class Menu {
private:
    Editor& editor;
    Umbral& umbral;       // unico filtro con parametro: se configura con su propia opcion
    bool finEntrada;      // true si se cerro la entrada (Ctrl+D)

    std::string recortar(const std::string& s) const;
    bool aEntero(const std::string& s, int& valor) const;
    bool leerLinea(const std::string& prompt, std::string& linea);
    bool leerEntero(const std::string& prompt, int minimo, int maximo, int& valor);

    void mostrarMenu() const;
    void ejecutar(int opcion);

    void opcionCargar();
    void opcionGuardar();
    void opcionListarFiltros() const;
    void opcionAplicarFiltro();
    void opcionConfigurarUmbral();
    void opcionDeshacer();
    void opcionInfo() const;
    void opcionGuardarBitacora();
    void opcionCargarBitacora();

public:
    Menu(Editor& editor, Umbral& umbral);
    void ejecutarBucle();
};

#endif
