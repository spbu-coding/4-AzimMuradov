cmake_minimum_required(VERSION 3.7)
project(tests LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(converter src/converter.c src/bmpl_bmp.c src/bmpl_err.c)
add_executable(comparer src/comparer.c src/bmpl_bmp.c src/bmpl_err.c)
