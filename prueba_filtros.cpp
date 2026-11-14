#include <iostream>
#include <iomanip>
#include <vector>
#include "pgm_io/pgm_io.h"
#include "Imagen.h"
#include "Filtro.h"
#include "Umbral.h"
#include "Media.h"
#include "Sobel.h"
#include "EspejoHorizontal.h"
#include "Rotar90.h"
#include "Mediana.h"
#include "CadenaFiltros.h"

using namespace std;

// Lectura y escritura con pgm_io solo para estas pruebas.
Imagen cargar(const string& ruta) {
    int alto = 0, ancho = 0, maxVal = 0;
    int** datos = leerPGM(ruta, alto, ancho, maxVal);
    if (datos == nullptr) {
        return Imagen(1, 1, 255);
    }
    Imagen img(alto, ancho, maxVal);
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            img(i, j) = datos[i][j];
        }
    }
    liberarPGM(datos, alto);
    return img;
}

void guardar(const Imagen& img, const string& ruta) {
    int** datos = asignarMatriz(img.getAlto(), img.getAncho());
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            datos[i][j] = img(i, j);
        }
    }
    if (escribirPGM(ruta, datos, img.getAlto(), img.getAncho(), img.getMaxVal())) {
        cout << "Guardado: " << ruta << endl;
    }
    liberarPGM(datos, img.getAlto());
}

void imprimir(const Imagen& img) {
    for (int i = 0; i < img.getAlto(); i++) {
        for (int j = 0; j < img.getAncho(); j++) {
            cout << setw(4) << img(i, j);
        }
        cout << endl;
    }
}

int main() {
    Umbral umbral(128);
    Media media;
    Sobel sobel;
    EspejoHorizontal espejo;
    Rotar90 rotar;
    Mediana mediana;

    vector<Filtro*> todos;
    todos.push_back(&umbral);
    todos.push_back(&media);
    todos.push_back(&sobel);
    todos.push_back(&espejo);
    todos.push_back(&rotar);
    todos.push_back(&mediana);

    cout << "===== juguete8x8.pgm =====" << endl;
    Imagen juguete = cargar("imagenes/juguete8x8.pgm");
    imprimir(juguete);
    for (int i = 0; i < (int)todos.size(); i++) {
        cout << endl << "-> " << todos[i]->nombre() << endl;
        imprimir(todos[i]->aplicar(juguete));
    }

    cout << endl << "===== Imagen 2x3 (no simetrica) para Espejo y Rotar90 =====" << endl;
    Imagen chica(2, 3, 255);
    int valor = 10;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            chica(i, j) = valor;
            valor = valor + 10;
        }
    }
    imprimir(chica);
    cout << "-> " << espejo.nombre() << endl;
    imprimir(espejo.aplicar(chica));
    cout << "-> " << rotar.nombre() << endl;
    imprimir(rotar.aplicar(chica));

    cout << endl << "===== retrato.pgm: un filtro a la vez =====" << endl;
    Imagen retrato = cargar("imagenes/retrato.pgm");
    guardar(umbral.aplicar(retrato), "retrato_umbral.pgm");
    guardar(media.aplicar(retrato), "retrato_media.pgm");
    guardar(sobel.aplicar(retrato), "retrato_sobel.pgm");
    guardar(espejo.aplicar(retrato), "retrato_espejo.pgm");
    guardar(rotar.aplicar(retrato), "retrato_rotar90.pgm");
    guardar(mediana.aplicar(retrato), "retrato_mediana.pgm");

    cout << endl << "===== retrato.pgm: cadena de filtros =====" << endl;
    CadenaFiltros cadena;
    cadena.agregar(&media);
    cadena.agregar(&sobel);
    cadena.agregar(&espejo);
    cadena.listar();
    guardar(cadena.aplicar(retrato), "retrato_cadena.pgm");

    cout << endl << "===== patron.pgm: Sobel =====" << endl;
    Imagen patron = cargar("imagenes/patron.pgm");
    guardar(sobel.aplicar(patron), "patron_sobel.pgm");

    return 0;
}
