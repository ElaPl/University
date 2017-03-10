/**
* @Plik:  widget.h
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera deklarację zmiennych globalnych i strury statusBar
*/

#ifndef WIDGET_H
#define WIDGET_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "dots.h"

GtkWidget *window;
GtkWidget *gridWindow;
GtkWidget *toolBar;
GtkWidget *toolGrid;

GtkWidget *help_window;
GtkWidget *help_container;
GtkWidget *win_window;
GtkWidget *win_container;
GtkWidget *about_window;
GtkWidget *about_container;
GtkWidget *edit_window;
GtkWidget *edit_container;

GtkWidget *line1;
GtkWidget *line2;
GtkToolItem *playButton;
GtkToolItem *resignButton;
GtkToolItem *aboutButton;
GtkToolItem *helpButton;
GtkToolItem *executeButton;

gchar player1_name[30];
gchar player2_name[30];

char infoText1[100];
char infoText2[100];

GdkRGBA *player1color;
GdkRGBA *player2color;

GtkWidget *player1_Grid;
GtkWidget *player2_Grid;

GtkWidget *frame1;
GtkWidget *frame2;

GtkWidget *infoAboutPlayer1;
GtkWidget *infoAboutPlayer2;

GtkWidget *colorOfPlayer1;
GtkWidget *colorOfPlayer2;

GtkWidget *gameWindow;
GtkWidget *drawingArea;

GtkWidget *entryNameP1;
GtkWidget *entryNameP2;


typedef struct {
    int numOfYourPieces, numOfMove, numOfGetsPieces;
    GtkWidget *etykieta;
} statusBar;

statusBar *statys1;
statusBar *statys2;
int counter;

int press_x;
int press_y;

#endif /* WIDGET_H */
