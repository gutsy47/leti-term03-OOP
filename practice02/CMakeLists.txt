cmake_minimum_required(VERSION 3.26)
project(practice02)

set(CMAKE_CXX_STANDARD 20)

add_executable(practice02 main02.cpp
        matrix.cpp
        matrix.h
        application.cpp
        application.h
        number.h
        mycomplex.h
        mycomplex.cpp)

