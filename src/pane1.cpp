#include "pane1.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

WINDOW* createPane1(int height, int width, int starty, int startx) {
    WINDOW* pane1 = newwin(height, width, starty, startx);
    box(pane1, 0, 0); // Draw border
    mvwprintw(pane1, 0, 1, "< Pane 1: Current Directory path >");

    fs::path currentPath = fs::current_path();
    mvwprintw(pane1, 1, 1, currentPath.string().c_str());

    // Add footer with hints at the bottom of pane1
    std::string footer_hint = "UP/DOWN - Navigate, ENTER - Open, BACKSPACE - Back, q - Quit";
    int footer_y = height - 3;
    mvwprintw(pane1, footer_y, 1, footer_hint.c_str());

    wrefresh(pane1);
    return pane1;
}


