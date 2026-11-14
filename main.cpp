#include "Editor.h"
#include "Menu.h"
#include "Umbral.h"
#include "Media.h"
#include "Sobel.h"
#include "EspejoHorizontal.h"
#include "Rotar90.h"
#include "Mediana.h"

// Los filtros viven en main (stack): el Editor solo guarda punteros (agregacion),
// asi que main es el dueno y no hay new/delete que olvidar.
int main() {
    Umbral umbral(128);
    Media media;
    Sobel sobel;
    EspejoHorizontal espejo;
    Rotar90 rotar;
    Mediana mediana;

    Editor editor;
    editor.registrarFiltro(&umbral);
    editor.registrarFiltro(&media);
    editor.registrarFiltro(&sobel);
    editor.registrarFiltro(&espejo);
    editor.registrarFiltro(&rotar);
    editor.registrarFiltro(&mediana);

    Menu menu(editor, umbral);
    menu.ejecutarBucle();
    return 0;
}
