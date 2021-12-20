cmake_minimum_required(VERSION 3.19)

project(SPP C)

set(CMAKE_C_STANDARD 99)

add_executable(
        SPP
        main.c
        matrix.c
        matrix.h
        time.h
        time.c
        coordinate.h
        coordinate.c
)