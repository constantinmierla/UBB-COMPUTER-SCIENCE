cmake_minimum_required(VERSION 3.27)
project(Lab2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
include_directories(.)

add_executable(Lab2
        main.c
        Domain/product.h
        Domain/product.c
        Repository/repository.h
        Repository/repository.c
        Tests/test.h
        Tests/tests.c
        Service/service.h
        Domain/validator.h
        Domain/validator.c
        Service/service.c
        UI/ui.c
        UI/ui.h)
