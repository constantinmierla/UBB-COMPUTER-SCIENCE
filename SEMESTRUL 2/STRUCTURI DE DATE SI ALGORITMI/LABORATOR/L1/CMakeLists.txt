cmake_minimum_required(VERSION 3.26)
project(L1)

set(CMAKE_CXX_STANDARD 17)

add_executable(L1 App.cpp
        "Iterator multime.cpp"
        "Iterator multime.h")
