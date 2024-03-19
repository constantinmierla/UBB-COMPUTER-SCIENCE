cmake_minimum_required(VERSION 3.26)
project(seminar_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(seminar_1 main.c
        cmake-build-debug/gestiune_melodii.c
        cmake-build-debug/gestiune_melodii.h)
