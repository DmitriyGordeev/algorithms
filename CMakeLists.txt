cmake_minimum_required(VERSION 3.5)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SORT_SRC
        src/Sort.cpp)

SET(TREE_SRC
        src/Tree.cpp)

set(SOURCE_FILES src/main.cpp
        ${SORT_SRC}
        ${TREE_SRC})
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


# Tree
set(TREE_TEST_SOURCE
        ${TREE_SRC}
        test/test_Tree.cpp)
add_executable(test_Tree ${TREE_TEST_SOURCE})
target_link_libraries(test_Tree ${GTEST_LIBS})