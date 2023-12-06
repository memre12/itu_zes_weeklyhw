cmake_minimum_required(VERSION 3.26)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Calculator
        Calculator.cpp
        Calculator.h
        main.cpp)
