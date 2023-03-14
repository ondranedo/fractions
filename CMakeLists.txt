cmake_minimum_required(VERSION 3.2)

project(zlomky)

add_subdirectory(demo)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

add_library(frac STATIC src/fractions64.c src/fractions64.h)