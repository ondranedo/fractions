cmake_minimum_required(VERSION 3.24)

project(zlomky)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

add_executable(zlomky src/main.c src/fractions.cpp src/fractions.h)