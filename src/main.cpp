#include <curses.h>
#include <iostream>
#include "pane1.h"
#include "pane2.h"
#include "pane3.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    int height, width;
    getmaxyx(stdscr, height, width);
    int pane_width = width / 3;

    WINDOW* pane1 = createPane1(height, pane_width, 0, 0);
    WINDOW* pane3 = createPane3(height, width - 2 * pane_width, 0, 2 * pane_width);
    WINDOW* pane2 = createPane2(height, pane_width, 0, pane_width, pane1, pane3);

    getch();

    delwin(pane1);
    delwin(pane2);
    delwin(pane3);
    endwin();

    return 0;
}
