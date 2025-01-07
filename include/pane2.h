#ifndef PANE2_H
#define PANE2_H

#include <curses.h>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

bool isTextFile(const std::string& filename);
std::string format_size(uintmax_t size);
std::string get_selected_filename(int selected_index);
void print_dir_contents (int height, int width, int pane_width, WINDOW *pane2, WINDOW *pane3, int selected_index);
void handle_navigation(int height, int width, int startx, WINDOW* pane1, WINDOW* pane2, WINDOW* pane3, fs::path initialized_dir);
WINDOW* createPane2(int height, int width, int starty, int startx, WINDOW* pane1, WINDOW* pane3);

#endif
