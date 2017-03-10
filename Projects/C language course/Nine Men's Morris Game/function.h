/**
* @Plik:  function.h
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera nagłóœki funkcji, które są wywoływane podczas działania programu
*/
#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "widget.h"
#include "dots.h"
#include <stdbool.h>

/**
* @opis funkcja przypisująca początkowe wartości:
* -zeruje licznik,]
* -zeruje wynik graczy
* -zmiennym isMillV i isMillH typu bool przypisuje wartości false
*/

void init();
/**
* @opis Funkcja obsługująca przycisk "New Game". Zaczyna nową grę
*/
void newGameButton(GtkWidget *widget, gpointer data);

/**
* @opis Funkcja obsługująca przycisk "ResignButton". Po naciśnięciu jeden z graczy rezygnuje z gry- czyli przegrywa. Funcja kończy rozgrywkę.
*/
void resignButtonfun(GtkWidget *widget, gpointer data);
/**
* @opis Funkcja obsługująca przycisk "HelpButton". Po naciśnięciuWyswietla okno z zasadami gry.
*/
void helpButtonfun(GtkWidget *widget, gpointer data);
/**
* @opis Funkcja obsługująca przycisk "ExecuteButton". Po naciśnięciu wyświetla się okno umożliwiające zmiane imion graczy.
*/
void changeNameButton(GtkWidget *widget, gpointer data);
/**
* @opis Funkcja obsługujące przycisk "AboutButton" Po naciśnięciu wyświetlają się informacje o twórcy gry.
*/
void aboutProgramButton(GtkWidget *widget, gpointer data);
/**
* @opis Funckcja wywołana przez changeNameButton. Pozwala na dodanie nowych znaków do imienia gracza 1.
*/
void insertChangeNameP1(GtkEditable *edit, gchar const *new_text, gint new_length, gpointer position, gpointer data);
/**
* @opis Funckcja wywołana przez changeNameButton. Pozwala na usunięcie znaków z imienia gracza 1.
*/
void delateChangeNameP1 (GtkEditable* edit, gint start_pos, gint end_pos, gpointer data);
/**
* @opis Funckcja wywołana przez changeNameButton. Pozwala na dodanie nowych znaków do imienia gracza 2.
*/
void insertChangeNameP2 (GtkEditable* edit, gchar const* new_text, gint new_length, gpointer position, gpointer data);
/**
* @opis Funckcja wywołana przez changeNameButton. Pozwala na usunięcie znaków z imienia gracza 2.
*/
void delateChangeNameP2 (GtkEditable* edit, gint start_pos, gint end_pos, gpointer data);
/**
* @opis Funckcja, która zmniejsza o 1 liczbę pionków gracza 1.
*/
void decreaseNumOfYourPiecesP1();
/**
* @opis Funckcja, która zmniejsza liczbę pionków gracza 2.
*/
void decreaseNumOfYourPiecesP2();
/**
* @opis Funckcja, która zwiększa o 1 liczbę ruchów gracza 1.
*/
void increaseNumOfMoveP1();
/**
* @opis Funckcja, która zwiększa o 1 liczbę ruchów gracza 2.
*/
void increaseNumOfMoveP2();
/**
* @opis Funckcja, która zwiększa o 1 liczbę zdobytych pionków gracza 1.
*/
void increaseNumOfGetsPiecesP1();
/**
* @opis Funckcja, która zwiększa o 1 liczbę zdobytych pionków gracza 2.
*/
void increaseNumOfGetsPiecesP2();
/**
* @opis Funckcja sprawdzająca czy pionki na planszy utworzyły pionowy młynek.
*/
bool isMillVertical(struct dot *point);
/**
* @opis Funckcja sprawdzająca czy pionki na planszy utworzyły poziomy młynek.
*/
bool isMillHorizontal(struct dot *point);
/**
* @opis Funkcja która uaktywania się w momencie, gdy isMillVertical, lub isMillHrizontal zwrócą true.
* Pozwala na zabranie pionka przeciwnikowi 2. I uaktywnia funkcję "increaseNumOfGetsPiecesP1".
* Sprawdza liczbę zdobytych pionków przeciwnika. Jeżeli jest równa 7, uaktywnia winEventP1;
*/
void millEventP1(struct dot *point);
/**
* @opis Funkcja która uaktywania się w momencie, gdy isMillVertical, lub isMillHrizontal zwrócą true.
* Pozwala na zabranie pionka przeciwnikowi 1. I uaktywnia funkcję "increaseNumOfGetsPiecesP2"
* Sprawdza liczbę zdobytych pionków przeciwnika. Jeżeli jest równa 7, uaktywnia winEventP1;
*/
void millEventP2(struct dot *point);
/**
* @opis Uaktywnia się, gdy liczba zdobytych gracza 1 jest równa 7. Wyśwletla nowe okno z informacją, który gracz wygrał.
* Okienko zawiera przycisk pozwalający na zrestartowanie gry .
*/
void winEventP1();
/**
* @opis Uaktywnia się, gdy liczba zdobytych gracza 2 jest równa 7. Wyśwletla nowe okno z informacją, który gracz wygrał.
* Okienko zawiera przycisk pozwalający na zrestartowanie gry.
*/
void winEventP2();
/**
* @opis Funkcja która ustawia domyślne kolory dla graczy.
*/
void setDefaultColor();



bool isMillV;
bool isMillH;

#endif /* FUNCTION_H */
