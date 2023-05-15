include_directories(../src/)

add_executable(test_bstree test_bstree.cpp ../src/bstree.cpp)
target_link_libraries(test_bstree Catch2::Catch2)

add_executable(test_avltree test_avltree.cpp ../src/avltree.cpp)
target_link_libraries(test_avltree Catch2::Catch2)

add_executable(test_sort test_sort.cpp ../src/sort.cpp)
target_link_libraries(test_sort Catch2::Catch2)