#ifndef ARCHIVOPGM_H
#define ARCHIVOPGM_H

#include <string>
#include <fstream>
#include "Imagen.h"

// Lee y escribe un archivo PGM. Formatos: 2 = P2 (texto), 5 = P5 (binario).
// Las operaciones devuelven true/false; el motivo del fallo queda en getError().
class ArchivoPGM {
private:
    std::string ruta;
    int formato;
    std::string error;

    bool fallar(const std::string& mensaje);
    bool leerToken(std::istream& f, std::string& token);
    bool leerEntero(std::istream& f, const std::string& que, int& valor);

public:
    ArchivoPGM(const std::string& ruta);

    std::string getRuta() const;
    int getFormato() const;
    std::string getNombreFormato() const;
    std::string getError() const;

    bool leer(Imagen& destino);
    bool escribir(const Imagen& img, int formato);
};

#endif
