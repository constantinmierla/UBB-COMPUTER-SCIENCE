cmake_minimum_required(VERSION 3.27)
project(L3)

set(CMAKE_CXX_STANDARD 17)

add_executable(L3 main.cpp
        IteratorMD.cpp
        MD.cpp
        TestExtins.cpp
        TestScurt.cpp)
