/**
* @Plik:  dots.h
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera deklarację  strury dot , tablicy struktur "pointsDefinitions" typu dot i nagłówek funkcji która przypisuje
* początkowe wartości do tej tablicy.
*/
#ifndef DOTS_H
#define DOTS_H
#include <stddef.h>

/**
* @opis Struktura opisująca pola na planszy
*
*   Przechowuje
* - Numer gracza:
*   --1 gdy na tym polu stoi gracz 1
*   --2 gdy na tym polu stoi gracz 2
*   --0 gdy to pole jest puste
* - Wstaźnik na dwie struktury, pola w lini poziomej, które mogą z tym polem tworzyć młynek
* - Wstaźnik na dwie struktury, pola w lini pionowej, które mogą z tym polem tworzyć młynek
* - 4 wskaźniki na pola na które gracz stojący na danym polu może się przemieścić (4 pola w odległośći 1 od tego)
*/
typedef struct dot {
    int player;
    double x, y;
    struct dot *horizontal1;
    struct dot *horizontal2;
    struct dot *vertical1;
    struct dot *vertical2;
    struct dot *possible1;
    struct dot *possible2;
    struct dot *possible3;
    struct dot *possible4;

} dot;

dot pointsDefinitions[24];

struct dot *pos1;
struct dot *pos2;
struct dot *pos3;
struct dot *pos4;
struct dot *pos5;
/**
* @opis funkcja przypisująca początkowe wartości do tablicy struktór "pointsDefinitions"
*/

void initPoints();

#endif /* DOTS_H */





