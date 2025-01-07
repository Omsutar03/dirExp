#include "pane1.h"
#include "pane2.h"
#include "pane3.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// Function to check if a file is a text file based on its extension
bool isTextFile(const std::string& filename) {
    std::string extension = filename.substr(filename.find_last_of('.') + 1);
    static const std::vector<std::string> textExtensions = {
        ".txt", ".md", ".log", ".cpp", ".h", ".cmake", ".py", ".html", 
        ".css", ".js", ".java", ".rb", ".php", ".pl", ".go", ".ts", 
        ".swift", ".rs", ".lua", ".sh", ".bat", ".ps1", ".scala", 
        ".r", ".sql", ".json", ".xml", ".yaml", ".yml", ".ini", 
        ".conf", ".toml", ".mdx", ".adoc", ".rst", ".tex", ".srt", 
        ".vtt", ".bib", ".tsv", ".ninja", ".a"
    };
    
    for (const auto& ext : textExtensions) {
        if (extension == ext) return true;
    }
    return false;
}

// Function to format the file size into a more readable format
std::string format_size(uintmax_t size) {
    const char* suffix[] = { "B", "KB", "MB", "GB" };
    int i = 0;
    while (size >= 1024 && i < 3) {
        size /= 1024;
        i++;
    }
    std::ostringstream oss;
    oss << size << " " << suffix[i];
    return oss.str();
}

std::string get_selected_filename(int selected_index) {
    int line_number = 1;
    for (const auto &entry : fs::directory_iterator(fs::current_path())) {
        // Get the filename
        std::string filename = entry.path().filename().string();

        if (line_number == selected_index) {
            return filename;
        }

        line_number++;
    }
    return "";  // Default return if index is out of range
}


void print_dir_contents (int height, int width, int pane_width, WINDOW *pane2, WINDOW *pane3, int selected_index) {
    int line_number = 1; // Start printing from line 1

    for(const auto &entry : fs::directory_iterator(fs::current_path())) {
        // Get just the filename
        std::string filename = entry.path().filename().string();

        // If current line matches selected_index, highlight it
        if (line_number == selected_index) {
            wattron(pane2, A_REVERSE); // Turn on reverse video mode (highlighting)

            if (isTextFile(filename)) {
                clearContentsOfPane3(pane3);
                displayTextFileInPane3(entry.path().string(), pane3);
                
            } else if (fs::is_directory(entry)) {
                clearContentsOfPane3(pane3);
                print_sub_dir_contents (height, width, pane_width, pane2, pane3, selected_index, filename);
            } else {
                clearContentsOfPane3(pane3);
            }
        }
        // Check if the entry is a regular file or a directory
        if (fs::is_regular_file(entry)) {
            // If it's a file, get its size
            uintmax_t filesize = fs::file_size(entry);
            std::string formatted_size = format_size(filesize);

            mvwprintw(pane2, line_number, 1, "%-40s %-10s", filename.c_str(), formatted_size.c_str()); // Print name and size
        } else if (fs::is_directory(entry)) {
            // If it's a directory, just mark it as "<DIR>"
            mvwprintw(pane2, line_number, 1, "%-40s <DIR>", filename.c_str());
        }

        // If current line matches selected_index, turn off the highlighting
        if (line_number == selected_index) {
            wattroff(pane2, A_REVERSE); // Turn off reverse video mode
        }

        line_number++;

        // Optional: prevent overflow
        if(line_number >= height - 1) break;
    }
};

void handle_navigation(int height, int width, int startx, WINDOW* pane1, WINDOW* pane2, WINDOW* pane3, fs::path initialized_dir) {
    int selected_index = 1; // Start at the first file
    int ch;

    // Handle user input
    while ((ch = getch()) != 'q') { // Press 'q' to quit
        // Get the parent directory
        std::string selected_filename = get_selected_filename(selected_index);
        fs::path sub_path = fs::current_path() / selected_filename;
        fs::path parent_path = fs::current_path().parent_path();
        mvwprintw(pane2, 15, 1, "%d", ch);
        wrefresh(pane2);
    
        switch (ch) {
            case 259: // Windows UP
            case 450: // Linux UP
                // Move up the list
                if (selected_index > 1) {
                    selected_index--;
                }
                // Clear the pane and print the directory contents with updated selection
                werase(pane2);  // Clear the window
                box(pane2, 0, 0);  // Redraw the border
                mvwprintw(pane2, 0, 1, "< Pane 2: Directory contents >");
                print_dir_contents(height, width, startx, pane2, pane3, selected_index);  // Print contents with selection
                wrefresh(pane2);  // Refresh the window to display the changes
                break;
            case 258: // Windows Down
            case 456: // Linux Down
                // Move down the list
                if (selected_index < std::distance(fs::directory_iterator(fs::current_path()), fs::directory_iterator())) {
                    selected_index++;
                }
                // Clear the pane and print the directory contents with updated selection
                werase(pane2);  // Clear the window
                box(pane2, 0, 0);  // Redraw the border
                mvwprintw(pane2, 0, 1, "< Pane 2: Directory contents >");
                print_dir_contents(height, width, startx, pane2, pane3, selected_index);  // Print contents with selection
                wrefresh(pane2);  // Refresh the window to display the changes
                break;
            case 8:
                selected_index = 1;
                // Simulate backspace
                // Ensure we're not at the root directory
                if (fs::current_path() != initialized_dir) {
                    // Change the current working directory to the parent directory
                    fs::current_path(parent_path);

                    // Updating path in pane1
                    wclear(pane1);
                    box(pane1, 0, 0); // Draw border
                    mvwprintw(pane1, 0, 1, "< Pane 1: Current Directory path >");
                    mvwprintw(pane1, 1, 1, fs::current_path().string().c_str());
                    std::string footer_hint = "UP/DOWN - Navigate, ENTER - Open, BACKSPACE - Back, q - Quit";
                    int footer_y = height - 3;
                    mvwprintw(pane1, footer_y, 1, footer_hint.c_str());
                    wrefresh(pane1);

                    // After changing the directory, refresh the file list in the pane
                    werase(pane2);  // Clear the window
                    box(pane2, 0, 0);  // Redraw the border
                    mvwprintw(pane2, 0, 1, "< Pane 2: Directory contents >");

                    // Reprint the directory contents with the updated directory
                    print_dir_contents(height, width, startx, pane2, pane3, selected_index);
                    wrefresh(pane2);  // Refresh the window to display the changes
                }
                break;
            case 10:
                selected_index = 1;
                // Simulate Enter
                if (fs::is_directory(sub_path)) {
                    // Change the current working directory to the selected directory
                    fs::current_path(sub_path);
                    
                    // Updating path in pane1
                    box(pane1, 0, 0); // Draw border
                    mvwprintw(pane1, 0, 1, "< Pane 1: Current Directory path >");
                    std::string footer_hint = "UP/DOWN - Navigate, ENTER - Open, BACKSPACE - Back, q - Quit";
                    int footer_y = height - 3;
                    mvwprintw(pane1, footer_y, 1, footer_hint.c_str());
                    mvwprintw(pane1, 1, 1, fs::current_path().string().c_str());
                    wrefresh(pane1);
                    

                    // After changing the directory, refresh the file list in the pane
                    werase(pane2);  // Clear the window
                    box(pane2, 0, 0);  // Redraw the border
                    mvwprintw(pane2, 0, 1, "< Pane 2: Directory contents >");

                    // Reprint the directory contents with the updated directory
                    print_dir_contents(height, width, startx, pane2, pane3, selected_index);
                    wrefresh(pane2);  // Refresh the window to display the changes
                }
                break;
        }
    }
}

WINDOW* createPane2(int height, int width, int starty, int startx, WINDOW* pane1, WINDOW* pane3) {
    WINDOW* pane2 = newwin(height, width, starty, startx);
    box(pane2, 0, 0);
    mvwprintw(pane2, 0, 1, "< Pane 2: Directory contents >");
    wrefresh(pane2);

    // Store the main directory application started in
    fs::path initialized_dir = fs::current_path();

    print_dir_contents(height, width, startx, pane2, pane3, 1);
    wrefresh(pane2);

    handle_navigation(height, width, startx, pane1, pane2, pane3, initialized_dir);
    wrefresh(pane2);

    return pane2;
}
