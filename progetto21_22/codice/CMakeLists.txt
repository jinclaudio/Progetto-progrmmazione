cmake_minimum_required(VERSION 3.16)
project(progetto21_22)

set(CMAKE_CXX_STANDARD 14)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(progetto21_22 main.cpp Structs.h Entity.cpp Entity.h Level.cpp Level.h Graphics.cpp Graphics.h Physics.cpp
        Physics.h Monster.cpp Monster.h Player.cpp Player.h)
target_link_libraries(progetto21_22 ${CURSES_LIBRARIES})
