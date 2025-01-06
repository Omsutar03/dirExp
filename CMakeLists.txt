cmake_minimum_required(VERSION 3.16)
project(dirExp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the header files from the "include" directory
include_directories(include)

# Add the source files and create the executable
add_executable(dirExp src/main.cpp src/pane1.cpp src/pane2.cpp src/pane3.cpp)

# Link the PDCurses library
if(WIN32)
    set(PDCURSES_LIB_PATH "${CMAKE_SOURCE_DIR}/libs/pdcurses.a")
    set(PDCURSES_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include")
    target_include_directories(dirExp PRIVATE ${PDCURSES_INCLUDE_PATH})
    target_link_libraries(dirExp PRIVATE ${PDCURSES_LIB_PATH})
endif()
