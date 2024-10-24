cmake_minimum_required(VERSION 3.27)
project(lab_7)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_executable(lab_7 main.cpp
        CarRepo.cpp
        CarRepo.h
        CarStore.cpp
        CarStore.h
        Console.cpp
        Console.h
        DynamicArray.h
        Exceptions.cpp
        Exceptions.h
        Masina.cpp
        Masina.h
        Test.cpp
        Test.h
        TestDynamicArray.cpp
        TestDynamicArray.h
        TestMasina.cpp
        TestMasina.h
        TestRepo.cpp
        TestRepo.h
        TestStore.cpp
        TestStore.h
        ValidatorMasina.cpp
        ValidatorMasina.h
        TestValidatorMasina.cpp
        TestValidatorMasina.h
)
