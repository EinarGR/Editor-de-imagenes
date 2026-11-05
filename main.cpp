#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#include "integrante1/Imagen.h"
#include "pgm_io.h"

using namespace std;

void guardarBitacoraEnDisco(const vector<string>& bitacora) {
    ofstream archivo("bitacora.txt");
    if (!archivo) {
        cout << "[Error] No se pudo guardar la bitacora en disco.\n";
        return;
    }
    for (const string& entrada : bitacora) {
        archivo << entrada << "\n";
    }
    cout << "Bitacora guardada exitosamente en 'bitacora.txt'.\n";
}

int main() {
    Imagen* imagenActual = nullptr; // Puntero para gestionar la memoria dinámica
    vector<string> bitacora;         // Lista para registrar el historial de operaciones
    int opcion = 0;

    do {
        cout << "\n=========================================\n";
        cout << "  PROCESADOR DE IMAGENES EN ESCALA DE GRISES\n";
        cout << "=========================================\n";
        cout << "1. Cargar o Guardar imagen (PGM)\n";
        cout << "2. Transformaciones con operadores (+, -, *, ~)\n";
        cout << "3. Cadena de filtros polimorficos (Integrante 2)\n";
        cout << "4. Consultar y persistir bitacora\n";
        cout << "5. Salir (Liberar memoria)\n";
        cout << "Seleccione una opcion [1-5]: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
            case 1: { // 1. Cargar y Guardar
                int subopcion;
                cout << "\n--- Cargar / Guardar ---\n";
                cout << "1. Cargar imagen PGM (P2)\n";
                cout << "2. Guardar imagen actual PGM\n";
                cout << "Opcion: ";
                cin >> subopcion;

                if (subopcion == 1) {
                    string ruta;
                    cout << "Ingrese la ruta del archivo a cargar (ej. juguete8x8.pgm): ";
                    cin >> ruta;

                    int alto = 0, ancho = 0, maxVal = 0;
                    int** pixeles = leerPGM(ruta, alto, ancho, maxVal);

                    if (pixeles != nullptr) {
                        // Si ya habia una imagen cargada, liberamos la anterior
                        delete imagenActual;
                        // Encapsulamos la nueva matriz
                        imagenActual = new Imagen(pixeles, alto, ancho, maxVal);

                        string registro = "Cargar imagen desde: " + ruta;
                        bitacora.push_back(registro);
                        cout << "-> Imagen cargada con exito (" << ancho << "x" << alto << ").\n";
                    }
                } else if (subopcion == 2) {
                    if (imagenActual == nullptr) {
                        cout << "[Aviso] No hay ninguna imagen cargada para guardar.\n";
                        break;
                    }
                    string ruta;
                    cout << "Ingrese el nombre/ruta para guardar: ";
                    cin >> ruta;

                    if (escribirPGM(ruta, imagenActual->getMatriz(),
                                   imagenActual->getAlto(), imagenActual->getAncho(),
                                   imagenActual->getValorMaximo())) {
                        string registro = "Guardar imagen en: " + ruta;
                        bitacora.push_back(registro);
                        cout << "-> Imagen guardada exitosamente.\n";
                    }
                }
                break;
            }

            case 2: { // 2. Operadores sobrecargados (Integrante 1)
                if (imagenActual == nullptr) {
                    cout << "[Aviso] Primero debe cargar una imagen (Opcion 1).\n";
                    break;
                }

                int opTransform;
                cout << "\n--- Transformaciones Puntuales (Sobrecarga de Operadores) ---\n";
                cout << "1. Aumentar brillo (+ escalar)\n";
                cout << "2. Disminuir brillo (- escalar)\n";
                cout << "3. Ajustar contraste (* factor real)\n";
                cout << "4. Invertir / Negativo (~)\n";
                cout << "Opcion: ";
                cin >> opTransform;

                if (opTransform == 1) {
                    int val;
                    cout << "Ingrese valor de brillo a sumar: ";
                    cin >> val;
                    *imagenActual = *imagenActual + val; // Operador +
                    bitacora.push_back("Operador: Brillo aumentado en +" + to_string(val));
                    cout << "-> Brillo aplicado.\n";
                } else if (opTransform == 2) {
                    int val;
                    cout << "Ingrese valor de brillo a restar: ";
                    cin >> val;
                    *imagenActual = *imagenActual - val; // Operador -
                    bitacora.push_back("Operador: Brillo reducido en -" + to_string(val));
                    cout << "-> Brillo reducido.\n";
                } else if (opTransform == 3) {
                    float factor;
                    cout << "Ingrese factor de contraste (ej. 1.5): ";
                    cin >> factor;
                    *imagenActual = *imagenActual * factor; // Operador *
                    bitacora.push_back("Operador: Contraste escalado x" + to_string(factor));
                    cout << "-> Contraste aplicado.\n";
                } else if (opTransform == 4) {
                    *imagenActual = ~(*imagenActual); // Operador ~
                    bitacora.push_back("Operador: Negativo aplicado (~)");
                    cout << "-> Imagen invertida a negativo.\n";
                }
                break;
            }

            case 3: { // 3. Jerarquía de filtros (Integrante 2)
                cout << "\n--- Filtros de la Jerarquia (Polimorfismo) ---\n";
                cout << "[Modulo asignado al Integrante 2]\n";
                break;
            }

            case 4: { // 4. Bitácora
                cout << "\n--- Bitacora de Operaciones ---\n";
                if (bitacora.empty()) {
                    cout << "No hay operaciones registradas todavia.\n";
                } else {
                    for (size_t i = 0; i < bitacora.size(); ++i) {
                        cout << (i + 1) << ". " << bitacora[i] << "\n";
                    }
                    cout << "\n¿Desea persistir la bitacora en disco? (1: Si, 0: No): ";
                    int guardar;
                    cin >> guardar;
                    if (guardar == 1) {
                        guardarBitacoraEnDisco(bitacora);
                    }
                }
                break;
            }

            case 5: // 5. Salir liberando memoria
                cout << "\nLiberando recursos de la aplicacion...\n";
                if (imagenActual != nullptr) {
                    delete imagenActual; // Llama al destructor de Imagen (0 fugas de memoria)
                    imagenActual = nullptr;
                }
                cout << "Memoria liberada correctamente. Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }

    } while (opcion != 5);

    return 0;
}