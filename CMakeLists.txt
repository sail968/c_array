cmake_minimum_required(VERSION 3.6)
project(c_array)

add_executable(c_array main.c src/array.c src/array.h tests/tests.c tests/tests.h)
