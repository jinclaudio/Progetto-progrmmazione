cmake_minimum_required(VERSION 3.17)
project(progetto)

set(CMAKE_CXX_STANDARD 14)

add_executable(progetto main.cpp
        src/Locate.cpp headers/Locate.h
        src/mappa.cpp headers/mappa.h src/personaggio.cpp headers/personaggio.h src/bonus_and_enemy.cpp headers/bonus_and_enemy.h)