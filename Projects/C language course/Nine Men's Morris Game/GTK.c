/**
* @Plik:  GTK.c
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera funkcje, które są wywoływane podczas tworzenia planszy
*/


#include "GTK.h"
#include "widget.h"


void createGameWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nine Men's Morris");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_window_set_default_size(GTK_WINDOW(window), 605, 400);

    gridWindow = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), gridWindow);
    createToolBar();
    createFieldOfPlayer1();
    createFieldOfPlayer2();

    createGameField();

    gtk_widget_show_all(window);
    gtk_main();
}

void createToolBar() {
    toolGrid = gtk_grid_new();
    line1 = gtk_image_new_from_file("line1.png");

    gtk_grid_attach(GTK_GRID(gridWindow), line1, 0, 0, 4, 3);
    gtk_grid_attach(GTK_GRID(gridWindow), toolGrid, 4, 0, 11, 1);

    toolBar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolBar), GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(toolBar), 10);

    aboutButton = gtk_tool_button_new(gtk_image_new_from_icon_name("help-about",GTK_ICON_SIZE_MENU), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), aboutButton, 0);
    g_signal_connect(G_OBJECT(aboutButton), "clicked", G_CALLBACK(aboutProgramButton), NULL);

    helpButton = gtk_tool_button_new(gtk_image_new_from_icon_name("system-help",GTK_ICON_SIZE_MENU), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), helpButton, 0);
    g_signal_connect(G_OBJECT(helpButton), "clicked", G_CALLBACK(helpButtonfun), NULL);

    executeButton = gtk_tool_button_new(gtk_image_new_from_icon_name("application-x-executable",GTK_ICON_SIZE_MENU), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), executeButton, 0);
    g_signal_connect(G_OBJECT(executeButton), "clicked", G_CALLBACK(changeNameButton), NULL);

    resignButton = gtk_tool_button_new(gtk_image_new_from_icon_name("process-stop",GTK_ICON_SIZE_MENU), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), resignButton, 0);
    g_signal_connect(G_OBJECT(resignButton), "clicked", G_CALLBACK(resignButtonfun), NULL);

    playButton = gtk_tool_button_new(gtk_image_new_from_icon_name("media-playback-start",GTK_ICON_SIZE_MENU), NULL);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), playButton, 0);
    g_signal_connect(G_OBJECT(playButton), "clicked", G_CALLBACK(newGameButton), NULL);


    gtk_grid_attach(GTK_GRID(toolGrid), toolBar, 5, 0, 10, 3);
    line2 = gtk_image_new_from_file("line1.png");
    gtk_grid_attach(GTK_GRID(gridWindow), line2, 15, 0, 1, 3);
}

void createFieldOfPlayer1() {

    player1_Grid = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(player1_Grid), 20);

    gtk_grid_attach(GTK_GRID(gridWindow), player1_Grid, 15, 8, 2, 1);

    sprintf(player1_name, "Player1");
    frame1 = gtk_frame_new(player1_name);
    gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_ETCHED_IN);
    gtk_container_add(GTK_CONTAINER(player1_Grid), frame1);

    sprintf(infoText1, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", 9, 0, 0);
    infoAboutPlayer1 = gtk_label_new(infoText1);

    gtk_box_pack_start(GTK_BOX(player1_Grid), infoAboutPlayer1, true, true, 3);

    colorOfPlayer1 = gtk_color_button_new_with_rgba(player1color);
    gtk_container_add(GTK_CONTAINER(player1_Grid), colorOfPlayer1);
    gtk_widget_set_size_request(colorOfPlayer1, 3, 5);

}

void createGameField() {
    gameWindow = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(gridWindow), gameWindow, 0, 8,10, 10);
    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingArea, 350, 450);

    statys1 = malloc(sizeof(statusBar));
    statys1->numOfYourPieces = 9;
    statys1->numOfGetsPieces = 0;
    statys1->numOfMove = 0;
    statys1->etykieta = infoAboutPlayer1;

    statys2 = malloc(sizeof(statusBar));
    statys2->numOfYourPieces = 9;
    statys2->numOfGetsPieces = 0;
    statys2->numOfMove = 0;
    statys2->etykieta = infoAboutPlayer2;


    counter = 0;
    g_signal_connect(drawingArea, "draw", G_CALLBACK(draw_background), NULL);


    gtk_grid_attach(GTK_GRID(gameWindow), drawingArea, 0, 0, 1, 1);
    g_signal_connect(drawingArea, "button-press-event", G_CALLBACK(button_press_event_cb), NULL);

    gtk_widget_set_events(drawingArea, gtk_widget_get_events(drawingArea)
            | GDK_BUTTON_PRESS_MASK
            | GDK_POINTER_MOTION_MASK);


}

void createFieldOfPlayer2() {
    player2_Grid = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(player2_Grid), 20);

    gtk_grid_attach(GTK_GRID(gridWindow), player2_Grid, 15, 11, 2, 1);

    sprintf(player2_name, "Player 2");
    frame2 = gtk_frame_new(player2_name);
    gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_ETCHED_IN);
    gtk_container_add(GTK_CONTAINER(player2_Grid), frame2);

    sprintf(infoText2, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", 9, 0, 0);
    infoAboutPlayer2 = gtk_label_new(infoText2);

    gtk_box_pack_start(GTK_BOX(player2_Grid), infoAboutPlayer2, true, true, 3);

    colorOfPlayer2 = gtk_color_button_new_with_rgba(player2color);
    gtk_container_add(GTK_CONTAINER(player2_Grid), colorOfPlayer2);
    gtk_widget_set_size_request(colorOfPlayer2, 3, 5);

}

void draw_background(GtkWidget *widget, cairo_t *mask, gpointer data) {
    cairo_set_source_rgba(mask, 0.9, 0.9, 0, 0.6);
    cairo_paint(mask);

    cairo_set_source_rgb(mask, 0, 0, 0);
    cairo_rectangle(mask, 15, 15, 320, 420);
    cairo_rectangle(mask, 60, 60, 230, 330);
    cairo_rectangle(mask, 105, 105, 140, 240);

    cairo_move_to(mask, 175, 15);
    cairo_line_to(mask, 175, 105);

    cairo_move_to(mask, 175, 435);
    cairo_line_to(mask, 175, 345);

    cairo_move_to(mask, 15, 225);
    cairo_line_to(mask, 105, 225);

    cairo_move_to(mask, 335, 225);
    cairo_line_to(mask, 245, 225);
    cairo_set_line_width(mask, 5);
    cairo_stroke(mask);

    cairo_set_line_cap(mask, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_width(mask, 20);

    for (int i = 0; i < 24; ++i) {
        if (pointsDefinitions[i].player == 0) {
            cairo_set_source_rgb(mask, 0, 0, 0);
            cairo_move_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_line_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_set_line_width(mask, 20);
            cairo_stroke(mask);
        }
        if (pointsDefinitions[i].player == 1) {
            gdk_cairo_set_source_rgba(mask, player1color);
            cairo_set_line_width(mask, 23);
            cairo_move_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_line_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_stroke(mask);
        }
        if (pointsDefinitions[i].player == 2) {
            gdk_cairo_set_source_rgba(mask, player2color);
            cairo_set_line_width(mask, 23);
            cairo_move_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_line_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_stroke(mask);
        }
        if (pointsDefinitions[i].player == 3) {
            cairo_set_source_rgb(mask, 1, 1, 1);
            cairo_set_line_width(mask, 23);
            cairo_move_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_line_to(mask, pointsDefinitions[i].x, pointsDefinitions[i].y);
            cairo_stroke(mask);
        }
    }
}

