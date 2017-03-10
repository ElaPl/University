/**
* @Plik:  GTK.h
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera definicje funkcji, które są wywoływane podczas tworzenia planszy
*/

#ifndef GTK_H
#define GTK_H

#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "dots.h"
/**
* @opis Tworzy główne okno gry i uruchamia funkcje odpowiedzialne za utworzenie innych elementów
*/
void createGameWindow();
/**
* @opis Funkcja Tworząca menu. Uruchamia również funkcje odpowiedzialne za czynności
* następujące po naciśnięciu przyniska
*/
void createToolBar();
/**
* @opis Funkcja Tworząca pole gracza 1. Tworzy jego status i opcję wyboru koloru
*/
void createFieldOfPlayer1();
/**
* @opis Funkcja Tworząca plansze do gry. Uruchamia funkcję odpowiedzialną za rysowanie pola gry, oraz funkcję
* pobierającą współrzędne punktu w którym użytkownik nacisną myszką.
*/
void createGameField();
/**
* @opis Funkcja Tworząca pole gracza 1. Tworzy jego status i opcję wyboru koloru
*/
void createFieldOfPlayer2();
/**
* @opis Funkcja rysująca pole do gry.
*/
void draw_background(GtkWidget *widget, cairo_t *mask, gpointer data);
/**
* @opis Funkcja wywoływana w momencie naciśnięcia myszką na planszę. Określa, który gracz wykonał ruch i czy jest on
* poprawny. Ponadto sprawdza czy nie ma młynka i kontroluje statusBar obydwuch graczy.
*/
void button_press_event_cb(GtkWidget *widget, GdkEventButton *event, gpointer data);

#endif
