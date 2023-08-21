cmake_minimum_required(VERSION 3.5)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)

# ================================================================
# Catch2 for testing
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)
include_directories(${catch2_SOURCE_DIR}/include/)

# ================================================================
add_executable(main
        src/main.cpp
        src/bstree.cpp
        src/avltree.cpp
        src/priority_queue_modified.cpp)
add_subdirectory(test/)