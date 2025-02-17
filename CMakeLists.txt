cmake_minimum_required(VERSION 3.16)

project(VisuallizationBST VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)

find_package(SFML 2.5 REQUIRED graphics window system)

add_executable(VisuallizationBST src/main.cpp)

target_link_libraries(VisuallizationBST sfml-graphics sfml-window sfml-system)
target_link_libraries(VisuallizationBST Textbox MainForm)
