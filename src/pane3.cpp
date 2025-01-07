#include "pane2.h"
#include "pane3.h"
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

WINDOW* createPane3(int height, int width, int starty, int startx) {
    WINDOW* pane3 = newwin(height, width, starty, startx);
    box(pane3, 0, 0); // Draw border
    mvwprintw(pane3, 0, 1, "< Pane 3: Preview of file or content of sub dir >");
    wrefresh(pane3);
    return pane3;
}

// Function to display the content of a text file in pane3
void displayTextFileInPane3(const std::string& filePath, WINDOW* pane3) {
    // Clear the pane and redraw the border
    werase(pane3);
    box(pane3, 0, 0);
    mvwprintw(pane3, 0, 1, "< Pane 3: Preview of file or content of sub dir >");
    wattron(pane3, A_REVERSE);
    mvwprintw(pane3, 1, 1, "<-- Preview of selected file -->");
    wattroff(pane3, A_REVERSE);

    // Open the file and read its contents
    std::ifstream file(filePath);
    if (!file) {
        mvwprintw(pane3, 1, 1, "Error: Unable to open file.");
        wrefresh(pane3);
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the entire file content into the buffer
    std::string content = buffer.str();

    int max_y, max_x;
    getmaxyx(pane3, max_y, max_x); // Get pane dimensions

    int row = 3; // Start printing from row 1 (row 0 is the title)
    int col = 1; // Start printing from column 1

    // Print content line by line
    std::istringstream contentStream(content);
    std::string line;
    while (std::getline(contentStream, line)) {
        // Truncate the line if it exceeds the pane's width
        if (line.length() > static_cast<size_t>(max_x - 2)) {
            line = line.substr(0, max_x - 3);
        }

        mvwprintw(pane3, row, col, line.c_str());
        row++;

        // Stop printing if we exceed the available height
        if (row >= max_y - 1) {
            mvwprintw(pane3, row, col, "(Content truncated)");
            break;
        }
    }

    wrefresh(pane3);
}

void clearContentsOfPane3(WINDOW* pane3) {
    // Clear the pane and redraw the border
    werase(pane3);
    box(pane3, 0, 0);
    mvwprintw(pane3, 0, 1, "< Pane 3: Preview of file or content of sub dir >");
    wrefresh(pane3);
}

void print_sub_dir_contents (int height, int width, int pane_width, WINDOW *pane2, WINDOW *pane3, int selected_index, std::string& current_file) {
    int line_number = 2;
    fs::path current_path = fs::current_path();

    fs::path sub_path = current_path / fs::path(current_file);
    sub_path = fs::canonical(sub_path);

    for(const auto &entry : fs::directory_iterator(sub_path)) {
        std::string filename = entry.path().filename().string();

        // Check if the entry is a regular file or a directory
        if (fs::is_regular_file(entry)) {
            // If it's a file, get its size
            uintmax_t filesize = fs::file_size(entry);
            std::string formatted_size = format_size(filesize);

            mvwprintw(pane3, line_number, 1, "%-40s %-10s", filename.c_str(), formatted_size.c_str()); // Print name and size
            
        } else if (fs::is_directory(entry)) {
            // If it's a directory, just mark it as "<DIR>"
            mvwprintw(pane3, line_number, 1, "%-40s <DIR>", filename.c_str());
            
        }
        wrefresh(pane3); // Refresh pane3

        line_number++;

        // Optional: prevent overflow
        if(line_number >= height - 1) break;
    }
}