cmake_minimum_required(VERSION 3.27)
project(lab_6_static)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_6_static main.cpp
        domain.cpp
        domain.h
        repository.cpp
        repository.h
        service.cpp
        service.h
        ui.cpp
        ui.h
        tests.cpp
        tests.h
        tests.h)
