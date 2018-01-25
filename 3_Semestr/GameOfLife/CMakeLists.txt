cmake_minimum_required(VERSION 3.7)
project(life)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Field.cpp
        Field.h)

add_executable(life ${SOURCE_FILES})