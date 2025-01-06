#ifndef PANE3_H
#define PANE3_H

#include <curses.h>
#include <string>

WINDOW* createPane3(int height, int width, int starty, int startx);
void displayTextFileInPane3(const std::string& filePath, WINDOW* pane3);
void clearContentsOfPane3(const std::string& filePath, WINDOW* pane3);
void print_sub_dir_contents (int height, int width, int pane_width, WINDOW *pane2, WINDOW *pane3, int selected_index, std::string& current_file);

#endif // PANE3_H
