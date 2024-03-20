cmake_minimum_required(VERSION 3.26)
project(lab_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab_2 main.c
        domain.c
        domain.h
        repository.c
        repository.h
        service.c
        service.h
        ui.c
        ui.h
        ui.h
        tests.c
        tests.h
        sort.c
        sort.h
        sort.h)
