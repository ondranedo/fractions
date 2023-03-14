set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

add_library(frac STATIC src/fractions64.cpp src/fractions64.h ../include/fractions64.h)