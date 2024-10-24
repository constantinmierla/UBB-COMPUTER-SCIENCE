cmake_minimum_required(VERSION 3.27)
project(L1)

set(CMAKE_CXX_STANDARD 17)

add_executable(L1 main.cpp
        Multime.cpp
        Multime.h
        IteratorMultime.cpp
        IteratorMultime.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
