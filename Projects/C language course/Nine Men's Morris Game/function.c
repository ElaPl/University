/**
* @Plik:  function.c
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera funkcje, które są wywoływane podczas działania programu
*/

#include "function.h"
#include "widget.h"
#include <gtk/gtk.h>



void init() {
    isMillV = false;
    isMillH = false;
    counter = 0;
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer1), infoText1);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer2), infoText2);

}
void newGameButton(GtkWidget *widget, gpointer data) {
    counter = 0;
    for (int i = 0; i < 24; i++) {
        pointsDefinitions[i].player = 0;
    }
    init();
    statys1->numOfYourPieces = 9;
    statys1->numOfGetsPieces = 0;
    statys1->numOfMove = 0;

    statys2->numOfYourPieces = 9;
    statys2->numOfGetsPieces = 0;
    statys2->numOfMove = 0;
    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
}
void resignButtonfun(GtkWidget *widget, gpointer data) {
    if (counter % 2 == 1)
        winEventP2();
    else
        winEventP1();
}
void helpButtonfun(GtkWidget *widget, gpointer data) {
    help_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(help_window), "HELP");
    g_signal_connect(help_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(help_window), 20);
    gtk_window_set_default_size(GTK_WINDOW(help_window), 300, 300);

    help_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_add(GTK_CONTAINER(help_window), help_container);
    char title[30];
    sprintf(title, "NINE MEN'S MORRIS");
    char help_text[2000];
    sprintf(help_text, "\n\n\nThe board consists of a grid with twenty-four intersections or points.\n Each player has nine pieces, or men, usually coloured red and blue.\n "
            "Players try to form 'mills'— three of their own men lined horizontally or\n vertically—allowing a player to remove an opponent's man from the game. A player wins \n"
            " by reducing the opponent to two pieces (where he could no longer form mills\n and thus be unable to win), or by leaving him without a legal move.\n"
            "The game proceeds in three phases:\n\n  1. Placing men on vacant points\n  2. Moving men to adjacent points\n\n"
            "PHARSE 1:\n\nThe game begins with an empty board. The players determine who plays first, then \ntake turns placing their men one per play on empty points. If a player is \n"
            "able to place three of his pieces in a straight line, vertically or horizontally, \nhe has formed a mill and may remove one of \n"
            "his opponent's pieces from the board and the game. Any piece can be chosen for the \nremoval, but a piece not in an opponent's mill must be selected, if possible.\n\n"
            "PHARSE 2:\n\nPlayers continue to alternate moves, this time moving a man to an adjacent\n point. A piece may not jump another piece. Players continue to try to form\n"
            " mills and remove their opponent's pieces in the same manner as in phase one. A player0\n may break a mill by moving one of his pieces out of an existing mill, then \n"
            "moving the piece back to form the same mill a second time (or any number of times), each \ntime removing one of his opponent's men. The act of removing an opponent's \n"
            "man is sometimes called pounding the opponent. When one player has been reduced to three \nmen, phase three begins.");


    GtkWidget *title_label;
    title_label = gtk_label_new(NULL);

    char *str = "<span foreground=\"red\" style=\"oblique\" size=\"x-large\"><b>%s</b></span>";
    char *markup;
    markup = g_markup_printf_escaped(str, title);
    gtk_label_set_markup(GTK_LABEL(title_label), markup);
    gtk_box_pack_start(GTK_BOX(help_container), title_label, FALSE, FALSE, 3);

    GtkWidget *help_label;
    help_label = gtk_label_new(help_text);
    gtk_box_pack_start(GTK_BOX(help_container), help_label, FALSE, FALSE, 3);

    gtk_widget_show_all(help_window);
    gtk_main();
}
void aboutProgramButton(GtkWidget *widget, gpointer data) {
    about_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(about_window), "HELP");
    gtk_container_set_border_width(GTK_CONTAINER(about_window), 20);
    gtk_window_set_default_size(GTK_WINDOW(about_window), 300, 150);

    about_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_add(GTK_CONTAINER(about_window), about_container);
    char title[30];
    sprintf(title, "Gra: Młynek\nAutor: Elżbieta Plaszczyk\nNumer indeksu: 273005");
    GtkWidget *title_label;
    title_label = gtk_label_new(NULL);

    char *str = "<span foreground=\"#8A0886\" style=\"oblique\"  gravity = \"west\" gravity_hint =\"strong\" size=\"x-large\"><b>%s</b> </span>";
    char *markup;
    markup = g_markup_printf_escaped(str, title);
    gtk_label_set_markup(GTK_LABEL(title_label), markup);
    gtk_box_pack_start(GTK_BOX(about_container), title_label, FALSE, FALSE, 3);
    gtk_widget_show_all(about_window);
    gtk_main();
}
void changeNameButton(GtkWidget *widget, gpointer data) {
    edit_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(edit_window), "CHANGE NAME");
    g_signal_connect(edit_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(edit_window), 20);
    gtk_window_set_default_size(GTK_WINDOW(edit_window), 300, 170);

    edit_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_add(GTK_CONTAINER(edit_window), edit_container);

    gchar title[30];
    sprintf(title, "Imie gracza 1:");
    GtkWidget *editName1;
    editName1 = gtk_label_new(title);
    gtk_container_add(GTK_CONTAINER(edit_container), editName1);

    entryNameP1 = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (edit_container), entryNameP1, FALSE, FALSE, 0);
    gtk_entry_set_text (GTK_ENTRY(entryNameP1), player1_name);
    g_signal_connect_after(GTK_WIDGET(entryNameP1), "insert-text", G_CALLBACK(insertChangeNameP1), NULL );
    g_signal_connect_after(GTK_WIDGET(entryNameP1), "delete-text", G_CALLBACK(delateChangeNameP1), NULL );


    gchar title2[30];
    sprintf(title2, "Imie gracza 2:");
    GtkWidget *editName2;
    editName2 = gtk_label_new(title2);
    gtk_container_add(GTK_CONTAINER(edit_container), editName2);

    entryNameP2 = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (edit_container), entryNameP2, FALSE, FALSE, 0);
    gtk_entry_set_text (GTK_ENTRY(entryNameP2), player2_name);
    g_signal_connect_after(GTK_WIDGET(entryNameP2), "insert-text", G_CALLBACK(insertChangeNameP2), NULL );
    g_signal_connect_after(GTK_WIDGET(entryNameP2), "delete-text", G_CALLBACK(delateChangeNameP2), NULL );


    gtk_widget_show_all(edit_window);
    gtk_main();

}
void insertChangeNameP1(GtkEditable *edit, gchar const *new_text, gint new_length, gpointer position, gpointer data) {
    new_text = gtk_entry_get_text(GTK_ENTRY (edit));
    gtk_frame_set_label(GTK_FRAME(frame1), new_text);
    sprintf(player1_name, new_text);
}
void delateChangeNameP1 (GtkEditable* edit, gint start_pos, gint end_pos, gpointer data) {
    const gchar* new_text = gtk_entry_get_text(GTK_ENTRY (edit));
    gtk_frame_set_label(GTK_FRAME(frame1), new_text);
    sprintf(player1_name, new_text);

}
void insertChangeNameP2 (GtkEditable *edit, gchar const *new_text, gint new_length, gpointer position, gpointer data) {
    new_text = gtk_entry_get_text(GTK_ENTRY (edit));
    gtk_frame_set_label(GTK_FRAME(frame2), new_text);
    sprintf(player2_name, new_text);

}
void delateChangeNameP2 (GtkEditable* edit, gint start_pos, gint end_pos, gpointer data) {
    const gchar* new_text = gtk_entry_get_text(GTK_ENTRY (edit));
    gtk_frame_set_label(GTK_FRAME(frame2), new_text);
    sprintf(player2_name, new_text);

}
void button_press_event_cb(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    press_x = (int) event->x;
    press_y = (int) event->y;
    for (int i = 0; i < 24; ++i) {
        if (sqrt(pow(((pointsDefinitions[i].x) - (event->x)), 2) + (pow(((pointsDefinitions[i].y) - (event->y)), 2))) < 20) {
            counter++;

            if (counter % 2 == 1) {  //ruch wykonal player1
                if (counter == 1)
                    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(colorOfPlayer1), player1color);

                if (isMillV) {
                    millEventP1(&pointsDefinitions[i]);
                    return;
                }
                if (isMillH) {
                    millEventP1(&pointsDefinitions[i]);
                    return;
                }

                if ((statys1->numOfYourPieces) > 0) {


                    if (counter > 18) {
                        if (pointsDefinitions[i].player == 2 || pointsDefinitions[i].player == 1) {
                            counter--;
                            return;
                        }

                        if (sqrt(pow(((pos1->x) - (event->x)), 2) + (pow(((pos1->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 1;
                            decreaseNumOfYourPiecesP1();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (sqrt(pow(((pos2->x) - (event->x)), 2) + (pow(((pos2->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 1;
                            decreaseNumOfYourPiecesP1();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (pos3 != NULL && sqrt(pow(((pos3->x) - (event->x)), 2) + (pow(((pos3->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 1;
                            decreaseNumOfYourPiecesP1();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (pos4 != NULL && sqrt(pow(((pos4->x) - (event->x)), 2) + (pow(((pos4->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 1;
                            decreaseNumOfYourPiecesP1();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (sqrt(pow(((pos5->x) - (event->x)), 2) + (pow(((pos5->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 1;
                            decreaseNumOfYourPiecesP1();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        counter--;
                        return;
                    }
                    if (counter < 18) {
                        if (pointsDefinitions[i].player == 1 || pointsDefinitions[i].player == 2) {
                            counter--;
                            return;
                        }
                        pointsDefinitions[i].player = 1;
                        decreaseNumOfYourPiecesP1();
                        gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                        if (isMillVertical(&pointsDefinitions[i])) {
                            counter--;
                            return;
                        }
                        if (isMillHorizontal(&pointsDefinitions[i])) {
                            counter--;
                            return;
                        }
                    }
                }
                else if (statys1->numOfYourPieces == 0) {
                    if (pointsDefinitions[i].player == 2 || pointsDefinitions[i].player == 0) {
                        counter--;
                        return;
                    }
                    pointsDefinitions[i].player = 0;
                    counter--;
                    statys1->numOfYourPieces++;
                    increaseNumOfMoveP1();
                    pos1 = pointsDefinitions[i].possible1;
                    pos2 = pointsDefinitions[i].possible2;
                    pos3 = pointsDefinitions[i].possible3;
                    pos4 = pointsDefinitions[i].possible4;
                    pos5 = &pointsDefinitions[i];

                    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                }
            }

            else if (counter % 2 == 0) {   //gracz2 wykonal ruch
                if (counter == 2)
                    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(colorOfPlayer2), player2color);
                if (isMillV) {
                    millEventP2(&pointsDefinitions[i]);
                    return;
                }
                if (isMillH) {
                    millEventP2(&pointsDefinitions[i]);
                    return;
                }
                if ((statys2->numOfYourPieces) > 0) {
                    if (counter > 18) {
                        if (pointsDefinitions[i].player == 2 || pointsDefinitions[i].player == 1) {
                            counter--;
                            return;
                        }

                        if (sqrt(pow(((pos1->x) - (event->x)), 2) + (pow(((pos1->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 2;
                            decreaseNumOfYourPiecesP2();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (sqrt(pow(((pos2->x) - (event->x)), 2) + (pow(((pos2->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 2;
                            decreaseNumOfYourPiecesP2();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (pos3 != NULL && sqrt(pow(((pos3->x) - (event->x)), 2) + (pow(((pos3->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 2;
                            decreaseNumOfYourPiecesP2();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (pos4 != NULL && sqrt(pow(((pos4->x) - (event->x)), 2) + (pow(((pos4->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 2;
                            decreaseNumOfYourPiecesP2();
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        if (sqrt(pow(((pos5->x) - (event->x)), 2) + (pow(((pos5->y) - (event->y)), 2))) < 20) {
                            pointsDefinitions[i].player = 2;
                            statys2->numOfYourPieces--;
                            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                            if (isMillVertical(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            if (isMillHorizontal(&pointsDefinitions[i])) {
                                counter--;
                                return;
                            }
                            return;
                        }
                        counter--;
                        return;
                    }
                    if (counter <= 18) {
                        if (pointsDefinitions[i].player == 2 || pointsDefinitions[i].player == 1) {
                            counter--;
                            break;
                        }
                        pointsDefinitions[i].player = 2;
                        decreaseNumOfYourPiecesP2();
                        gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                        if (isMillVertical(&pointsDefinitions[i])) {
                            counter--;
                            return;
                        }
                        if (isMillHorizontal(&pointsDefinitions[i])) {
                            counter--;
                            return;
                        }
                    }
                }
                else if (statys2->numOfYourPieces == 0) {
                    if (pointsDefinitions[i].player == 1 || pointsDefinitions[i].player == 0) {
                        counter--;
                        return;
                    }
                    pointsDefinitions[i].player = 0;
                    counter--;
                    statys2->numOfYourPieces++;
                    pos1 = pointsDefinitions[i].possible1;
                    pos2 = pointsDefinitions[i].possible2;
                    pos3 = pointsDefinitions[i].possible3;
                    pos4 = pointsDefinitions[i].possible4;
                    pos5 = &pointsDefinitions[i];
                    increaseNumOfMoveP2();

                    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
                }
            }
        }
    }
}
void decreaseNumOfYourPiecesP1() {
    (statys1->numOfYourPieces)--;
    char tab[20000];
    sprintf(tab, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", statys1->numOfYourPieces, statys1->numOfMove, statys1->numOfGetsPieces);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer1), tab);
    return;
}
void decreaseNumOfYourPiecesP2() {
    (statys2->numOfYourPieces)--;
    char tab[20000];
    sprintf(tab, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", statys2->numOfYourPieces, statys2->numOfMove, statys2->numOfGetsPieces);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer2), tab);
    return;
}
void increaseNumOfMoveP1() {
    (statys1->numOfMove)++;
    char tab[20000];
    sprintf(tab, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", statys1->numOfYourPieces, statys1->numOfMove, statys1->numOfGetsPieces);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer1), tab);
    return;
}
void increaseNumOfMoveP2() {
    (statys2->numOfMove)++;
    char tab[20000];
    sprintf(tab, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", statys2->numOfYourPieces, statys2->numOfMove, statys2->numOfGetsPieces);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer2), tab);
    return;
}
void increaseNumOfGetsPiecesP1() {
    (statys1->numOfGetsPieces)++;
    char tab[20000];
    sprintf(tab, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", statys1->numOfYourPieces, statys1->numOfMove, statys1->numOfGetsPieces);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer1), tab);
    return;
}
void increaseNumOfGetsPiecesP2() {
    (statys2->numOfGetsPieces)++;
    char tab[20000];
    sprintf(tab, "Liczba Twoich pionków: %d\n\nLiczba ruchów: %d\n\nLiczba zdobytych\npionków przeciwnika: %d\n", statys2->numOfYourPieces, statys2->numOfMove, statys2->numOfGetsPieces);
    gtk_label_set_text(GTK_LABEL(infoAboutPlayer2), tab);
    return;
}
void setDefaultColor() {
    player1color = (GdkRGBA *) malloc(sizeof(GdkRGBA));
    player1color->blue = 256 * 128;
    player1color->green = 0;
    player1color->red = 0;
    player1color->alpha = 1.0;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(colorOfPlayer1), player1color);

    player2color = (GdkRGBA *) malloc(sizeof(GdkRGBA));
    player2color->blue = 0;
    player2color->green = 0;
    player2color->red = 256 * 128;
    player2color->alpha = 1.0;

    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(colorOfPlayer2), player2color);
}
bool isMillHorizontal(struct dot *point) {
    int NumberOfPlayer;
    NumberOfPlayer = point -> player;
    if (point->horizontal1->player == NumberOfPlayer) {
        if (point->horizontal2->player == NumberOfPlayer) {
            point->horizontal1->player = 3;
            point->horizontal2->player = 3;
            point->player = 3;
            isMillH = true;

            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
            return true;
        }
    }
    return false;
}
bool isMillVertical(struct dot *point) {
    int NumberOfPlayer;
    NumberOfPlayer = point -> player;
    if (point->vertical1->player == NumberOfPlayer) {
        if (point->vertical2->player == NumberOfPlayer) {
            point->vertical1->player = 3;
            point->vertical2->player = 3;
            point->player = 3;
            isMillV = true;

            gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
            return true;
        }
    }
    return false;
}
void millEventP1(struct dot *point) {
    if (point->player == 1 || point->player == 0) {
        counter--;
        return;
    }
    point->player = 0;
    increaseNumOfGetsPiecesP1();
    if(isMillH) {
        for (int w = 0; w < 24; w++) {
            if (pointsDefinitions[w].player == 3)
                pointsDefinitions[w].player = 1;
        }
        isMillH = false;
    }
    if(isMillV) {
        for (int w = 0; w < 24; w++) {
            if (pointsDefinitions[w].player == 3)
                pointsDefinitions[w].player = 1;
        }
        isMillV = false;
    }
    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
    if (statys1 -> numOfGetsPieces >= 7) {
        statys1 -> numOfGetsPieces = 10;
        winEventP1();
    }
}
void millEventP2(struct dot *point) {
    if (point->player == 2 || point->player == 0) {
        counter--;
        return;
    }
    point->player = 0;
    increaseNumOfGetsPiecesP2();
    if(isMillH) {
        for (int w = 0; w < 24; w++) {
            if (pointsDefinitions[w].player == 3)
                pointsDefinitions[w].player = 2;
        }
        isMillH = false;
    }
    if(isMillV) {
        for (int w = 0; w < 24; w++) {
            if (pointsDefinitions[w].player == 3)
                pointsDefinitions[w].player = 2;
        }
        isMillV = false;
    }
    gtk_widget_queue_draw(GTK_WIDGET(drawingArea));
    if (statys2 -> numOfGetsPieces >= 7) {
        statys2 -> numOfGetsPieces = 10;

        winEventP2();
    }

}
void winEventP1() {

    win_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win_window), "Player 1 win");
    g_signal_connect(win_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(win_window), 20);
    gtk_window_set_default_size(GTK_WINDOW(win_window), 100, 70);

    win_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_add(GTK_CONTAINER(win_window), win_container);

    char title[30];
    sprintf(title, "%s wygrał", player1_name);

    GtkWidget *title_label;
    title_label = gtk_label_new(NULL);

    char *str = "<span foreground=\"blue\" style=\"oblique\" size=\"x-large\"><b>%s</b></span>";
    char *markup;
    markup = g_markup_printf_escaped(str, title);
    gtk_label_set_markup(GTK_LABEL(title_label), markup);
    gtk_box_pack_start(GTK_BOX(win_container), title_label, FALSE, FALSE, 3);
    GtkWidget *newGame;
    newGame = gtk_button_new_with_label("Nowa gra");
    g_signal_connect(G_OBJECT(newGame), "clicked", G_CALLBACK(newGameButton), NULL);
    gtk_container_add(GTK_CONTAINER(win_container), newGame);
    gtk_widget_show_all(win_window);
    gtk_main();

}
void winEventP2() {
    GtkWidget *win_window;
    GtkWidget *win_container;
    win_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win_window), "Player 2 win");
    g_signal_connect(win_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(win_window), 20);
    gtk_window_set_default_size(GTK_WINDOW(win_window), 100, 70);

    win_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_add(GTK_CONTAINER(win_window), win_container);

    char title[30];
    sprintf(title, "%s  wygrał", player2_name);

    GtkWidget *title_label;
    title_label = gtk_label_new(NULL);

    char *str = "<span foreground=\"red\" style=\"oblique\" size=\"x-large\"><b>%s</b></span>";
    char *markup;
    markup = g_markup_printf_escaped(str, title);
    gtk_label_set_markup(GTK_LABEL(title_label), markup);
    gtk_box_pack_start(GTK_BOX(win_container), title_label, FALSE, FALSE, 3);
    GtkWidget *newGame;
    newGame = gtk_button_new_with_label("Nowa gra");
    g_signal_connect(G_OBJECT(newGame), "clicked", G_CALLBACK(newGameButton), NULL);
    gtk_container_add(GTK_CONTAINER(win_container), newGame);
    gtk_widget_show_all(win_window);
    gtk_main();
}

