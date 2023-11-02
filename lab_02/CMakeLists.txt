cmake_minimum_required(VERSION 3.26)
project(lab02 C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(lab02
        inc/commands.h
        inc/consts.h
        inc/input.h
        inc/key_and_sort.h
        src/commands.c
        src/input.c
        src/key_and_sort.c
        src/main.c)
