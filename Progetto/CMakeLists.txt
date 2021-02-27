cmake_minimum_required(VERSION 3.17)
project(progetto)

set(CMAKE_CXX_STANDARD 14)

add_executable(progetto main.cpp
         Locate.cpp Locate.h Map.cpp Map.h)