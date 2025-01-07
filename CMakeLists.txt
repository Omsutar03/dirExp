cmake_minimum_required(VERSION 3.16)
project(dirExp VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the header files from the "include" directory
include_directories(include)

# Add the source files and create the executable
add_executable(dirExp src/main.cpp src/pane1.cpp src/pane2.cpp src/pane3.cpp)

# Find the required libraries
if(WIN32)
    # PDCurses setup for Windows
    set(PDCURSES_LIB_PATH "${CMAKE_SOURCE_DIR}/libs/pdcurses.a")
    set(PDCURSES_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include")
    target_include_directories(dirExp PRIVATE ${PDCURSES_INCLUDE_PATH})
    target_link_libraries(dirExp PRIVATE ${PDCURSES_LIB_PATH})
elseif(UNIX)
    # ncurses setup for Linux (Ubuntu/Arch)
    find_package(Curses REQUIRED)
    target_link_libraries(dirExp PRIVATE ${CURSES_LIBRARIES})
    target_include_directories(dirExp PRIVATE ${CURSES_INCLUDE_DIR})
endif()

# Set the install prefix (for Windows and Linux)
if(WIN32)
    # Use a relative path for Windows installation
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/dirExp")
elseif(UNIX)
    # For Linux, install to /usr/local/bin
    set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

# Install the executable to the bin directory inside the install prefix
install(TARGETS dirExp DESTINATION bin)

# Install headers and source (optional, for easier access to source code)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY src/ DESTINATION src)

# Packaging (for distribution)
include(CPack)

# Add CPack configurations for creating .deb (Ubuntu/Arch) or .zip (Windows)
set(CPACK_GENERATOR "ZIP;DEB;NSIS")
set(CPACK_PACKAGE_NAME "dirExp")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "Om Sutar <omsutar03@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libncurses-dev")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_ARCHITECTURE "all")
