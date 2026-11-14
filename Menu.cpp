#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(Editor& editor, Umbral& umbral) : editor(editor), umbral(umbral) {
    finEntrada = false;
}

string Menu::recortar(const string& s) const {
    int inicio = 0;
    int fin = (int)s.size() - 1;
    while (inicio <= fin && (s[inicio] == ' ' || s[inicio] == '\t' || s[inicio] == '\r')) {
        inicio++;
    }
    while (fin >= inicio && (s[fin] == ' ' || s[fin] == '\t' || s[fin] == '\r')) {
        fin--;
    }
    return s.substr(inicio, fin - inicio + 1);
}

// Convierte texto a entero sin excepciones: solo digitos, hasta 9 caracteres.
bool Menu::aEntero(const string& s, int& valor) const {
    if (s.empty() || s.size() > 9) {
        return false;
    }
    int resultado = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
        resultado = resultado * 10 + (s[i] - '0');
    }
    valor = resultado;
    return true;
}

bool Menu::leerLinea(const string& prompt, string& linea) {
    cout << prompt;
    if (!getline(cin, linea)) {
        finEntrada = true;
        return false;
    }
    linea = recortar(linea);
    return true;
}

bool Menu::leerEntero(const string& prompt, int minimo, int maximo, int& valor) {
    while (true) {
        string linea;
        if (!leerLinea(prompt, linea)) {
            return false;
        }
        int v;
        if (aEntero(linea, v) && v >= minimo && v <= maximo) {
            valor = v;
            return true;
        }
        cout << "Entrada invalida: ingrese un entero entre " << minimo << " y " << maximo << endl;
    }
}

void Menu::mostrarMenu() const {
    cout << "\n===== PROCESADOR DE IMAGENES =====" << endl;
    cout << " 1) Cargar imagen          2) Guardar imagen" << endl;
    cout << " 3) Listar filtros         4) Aplicar filtro" << endl;
    cout << " 5) Configurar umbral      6) Deshacer ultima operacion" << endl;
    cout << " 7) Info de la imagen      8) Ver bitacora" << endl;
    cout << " 9) Guardar bitacora      10) Cargar bitacora" << endl;
    cout << " 0) Salir" << endl;
}

void Menu::opcionCargar() {
    string ruta;
    if (!leerLinea("Ruta del archivo PGM: ", ruta)) {
        return;
    }
    if (ruta.empty()) {
        cout << "La ruta no puede estar vacia" << endl;
        return;
    }
    if (editor.cargar(ruta)) {
        cout << "Imagen cargada: " << editor.getImagen().getAncho() << "x"
             << editor.getImagen().getAlto() << endl;
    } else {
        cout << "Error: " << editor.getError() << endl;
    }
}

void Menu::opcionGuardar() {
    if (!editor.tieneImagen()) {
        cout << "Primero cargue una imagen" << endl;
        return;
    }
    string ruta;
    if (!leerLinea("Ruta de salida: ", ruta)) {
        return;
    }
    if (ruta.empty()) {
        cout << "La ruta no puede estar vacia" << endl;
        return;
    }
    int opcion;
    if (!leerEntero("Formato (1 = P2 texto, 2 = P5 binario): ", 1, 2, opcion)) {
        return;
    }
    int formato = 2;
    if (opcion == 2) {
        formato = 5;
    }
    if (editor.guardar(ruta, formato)) {
        cout << "Guardado en " << ruta << endl;
    } else {
        cout << "Error: " << editor.getError() << endl;
    }
}

void Menu::opcionListarFiltros() const {
    for (int i = 0; i < editor.getCantidadFiltros(); i++) {
        cout << " " << i + 1 << ") " << editor.nombreFiltro(i) << endl;
    }
}

void Menu::opcionAplicarFiltro() {
    if (!editor.tieneImagen()) {
        cout << "Primero cargue una imagen" << endl;
        return;
    }
    opcionListarFiltros();
    int n = editor.getCantidadFiltros();
    int opcion;
    if (!leerEntero("Filtro a aplicar (0 = cancelar): ", 0, n, opcion) || opcion == 0) {
        return;
    }
    if (editor.aplicarFiltro(opcion - 1)) {
        cout << "Aplicado: " << editor.nombreFiltro(opcion - 1)
             << " (deshacer disponible: " << editor.getCantidadDeshacer() << ")" << endl;
    } else {
        cout << "Error: " << editor.getError() << endl;
    }
}

void Menu::opcionConfigurarUmbral() {
    if (!editor.tieneImagen()) {
        cout << "Primero cargue una imagen" << endl;
        return;
    }
    int maxVal = editor.getImagen().getMaxVal();
    int valor;
    if (!leerEntero("Nuevo umbral (0-" + to_string(maxVal) + "): ", 0, maxVal, valor)) {
        return;
    }
    umbral.setUmbral(valor);
    editor.getBitacora().agregar("Umbral configurado en " + to_string(valor));
    cout << "Umbral = " << umbral.getUmbral() << endl;
}

void Menu::opcionDeshacer() {
    if (editor.deshacer()) {
        cout << "Ultima operacion deshecha" << endl;
    } else {
        cout << editor.getError() << endl;
    }
}

void Menu::opcionInfo() const {
    if (!editor.tieneImagen()) {
        cout << "No hay imagen cargada" << endl;
        return;
    }
    const Imagen& img = editor.getImagen();
    cout << "Archivo: " << editor.getRutaActual() << endl;
    cout << "Dimensiones: " << img.getAncho() << " x " << img.getAlto()
         << "  maxVal: " << img.getMaxVal() << endl;
    cout << "Operaciones que se pueden deshacer: " << editor.getCantidadDeshacer() << endl;
}

void Menu::opcionGuardarBitacora() {
    string ruta;
    if (!leerLinea("Ruta de la bitacora [bitacora.txt]: ", ruta)) {
        return;
    }
    if (ruta.empty()) {
        ruta = "bitacora.txt";
    }
    if (editor.getBitacora().guardar(ruta)) {
        cout << "Bitacora guardada en " << ruta << endl;
    } else {
        cout << "Error: " << editor.getBitacora().getError() << endl;
    }
}

void Menu::opcionCargarBitacora() {
    string ruta;
    if (!leerLinea("Ruta de la bitacora [bitacora.txt]: ", ruta)) {
        return;
    }
    if (ruta.empty()) {
        ruta = "bitacora.txt";
    }
    if (editor.getBitacora().cargar(ruta)) {
        cout << "Bitacora cargada (" << editor.getBitacora().getCantidad() << " entradas)" << endl;
    } else {
        cout << "Error: " << editor.getBitacora().getError() << endl;
    }
}

void Menu::ejecutar(int opcion) {
    switch (opcion) {
        case 1: opcionCargar(); break;
        case 2: opcionGuardar(); break;
        case 3: opcionListarFiltros(); break;
        case 4: opcionAplicarFiltro(); break;
        case 5: opcionConfigurarUmbral(); break;
        case 6: opcionDeshacer(); break;
        case 7: opcionInfo(); break;
        case 8: editor.getBitacora().listar(cout); break;
        case 9: opcionGuardarBitacora(); break;
        case 10: opcionCargarBitacora(); break;
        default: break;
    }
}

void Menu::ejecutarBucle() {
    int opcion = -1;
    while (opcion != 0 && !finEntrada) {
        mostrarMenu();
        if (!leerEntero("Opcion: ", 0, 10, opcion)) {
            break;
        }
        ejecutar(opcion);
    }
    cout << "Hasta luego" << endl;
}
