cmake_minimum_required(VERSION 3.27)
project(L7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(L7
        AB.cpp
        AB.h
        App.cpp
        IteratorAB.cpp
        IteratorAB.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
