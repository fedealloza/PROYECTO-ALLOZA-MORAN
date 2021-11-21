cmake_minimum_required(VERSION 3.20)
project(PROYECTO_FINAL)

set(CMAKE_CXX_STANDARD 14)

add_executable(PROYECTO_FINAL main.cpp Juego.cpp Juego.h Juego_facil.cpp Juego_facil.h Juego_dificil.cpp Juego_dificil.h MainMenu.cpp MainMenu.h)



include_directories("C:\\mingw64\\include")
#find_package(SFML 2.5 COMPONENTS system window graphics)

target_link_libraries(PROYECTO_FINAL sfml-system sfml-window sfml-graphics sfml-audio)