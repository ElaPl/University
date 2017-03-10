/**
* @Plik:  main.c
* @Autor: Elżbieta Plaszczyk
* @opis:  plik main
*/
#include "GTK.h"
#include "dots.h"
#include "function.h"

int main(int argc, char *argv[]) {
    initPoints();
    setDefaultColor();
    init();
    gtk_init(&argc, &argv);
    createGameWindow();

    return 0;
}

