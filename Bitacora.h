#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <vector>
#include <iostream>

// Historial de operaciones, guardable en disco y recargable.
// Archivo: primera linea "BITACORA v1", luego una operacion por linea.
class Bitacora {
private:
    std::vector<std::string> entradas;
    std::string error;

public:
    void agregar(const std::string& texto);
    int getCantidad() const;
    std::string getEntrada(int i) const;   // "" si el indice no existe
    std::string getError() const;
    void limpiar();
    void listar(std::ostream& os) const;

    bool guardar(const std::string& ruta);
    bool cargar(const std::string& ruta);  // reemplaza el contenido solo si tiene exito
};

#endif
