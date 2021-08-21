cmake_minimum_required(VERSION 3.19)
project(Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(headers)
include_directories(src)

add_executable(Game
        headers/map.h
        headers/utilities.h
        src/map.cpp
        src/utilities.cpp
        curses.h
        main.cpp src/character.cpp headers/character.h src/graphics.cpp headers/graphics.h src/Controls.cpp headers/Controls.h src/points.cpp headers/points.h)
