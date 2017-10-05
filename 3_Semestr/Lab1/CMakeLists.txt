cmake_minimum_required(VERSION 3.7)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp flat_map.h student.h)
add_executable(Lab1 ${SOURCE_FILES})