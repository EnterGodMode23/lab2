cmake_minimum_required(VERSION 3.26)
project(lab1 C)

set(CMAKE_C_STANDARD 17)

add_executable(
        lab1
        node.h
        node.c
        main_lab_2.c
        error.c
        main_lab_2.h
)
