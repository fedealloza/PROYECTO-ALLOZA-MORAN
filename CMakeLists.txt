cmake_minimum_required(VERSION 3.15)
project(proyecto-infoII)

set(CMAKE_CXX_STANDARD 14)

add_executable(proyecto main.cpp)
target_link_libraries(proyecto sfml-graphics sfml-audio sfml-system sfml-window)
