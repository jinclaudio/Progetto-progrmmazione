cmake_minimum_required(VERSION 3.17)
project(progetto)

set(CMAKE_CXX_STANDARD 14)

add_executable(progetto main.cpp
        src/Locate.cpp headers/Locate.h src/Map.cpp headers/Map.h)