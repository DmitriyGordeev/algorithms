cmake_minimum_required(VERSION 3.5)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Sorters.cpp Sorters.h)
add_executable(algorithms ${SOURCE_FILES})