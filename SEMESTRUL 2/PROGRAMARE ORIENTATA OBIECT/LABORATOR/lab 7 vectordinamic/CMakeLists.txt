cmake_minimum_required(VERSION 3.27)
project(lab_7_vectordinamic)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_7_vectordinamic main.cpp
        Pet.cpp
        Pet.h
        VectDinNewDelete.cpp
        VectDinNewDelete.h
        VectDinSmartPointer.cpp
        VectDinSmartPointer.h
        VectorDinamicTemplate.h)
