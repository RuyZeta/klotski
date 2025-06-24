cmake_minimum_required(VERSION 3.29)
project(bloques)

set(CMAKE_CXX_STANDARD 14)

add_executable(bloques main.cpp
        piezas.cpp
        piezas.h)
