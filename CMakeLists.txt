cmake_minimum_required(VERSION 3.5)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SORT_SRC
        src/Sort.cpp src/Sort.h)

set(SOURCE_FILES src/main.cpp ${SORT_SRC})
add_executable(algorithms ${SOURCE_FILES})

# -----------------------------------------------------------
# unit tests
set(GTEST_LIBS
        gtest
        gtest_main
        -pthread)

# Sort
set(SORT_TEST_SOURCE
        ${SORT_SRC}
        test/test_Sort.cpp)
add_executable(test_Sort ${SORT_TEST_SOURCE})
target_link_libraries(test_Sort ${GTEST_LIBS})