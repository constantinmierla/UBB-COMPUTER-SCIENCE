cmake_minimum_required(VERSION 3.26)
project(Multime__cu_rel_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Multime__cu_rel_
        IteratorMultime.cpp
        IteratorMultime.h
        Multime.cpp
        Multime.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h
        App.cpp)
