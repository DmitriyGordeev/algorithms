include_directories(../src/)

add_executable(test_bstree
        test_bstree.cpp
        ../src/bstree.cpp)
target_link_libraries(test_bstree Catch2::Catch2)

add_executable(test_avltree
        test_avltree.cpp
        ../src/avltree.cpp)
target_link_libraries(test_avltree Catch2::Catch2)

add_executable(test_sort
        test_sort.cpp
        ../src/sort.cpp)
target_link_libraries(test_sort Catch2::Catch2)

add_executable(test_bucketsort
        test_bucket_sort.cpp
        ../src/bucket_sort.cpp)
target_link_libraries(test_bucketsort Catch2::Catch2)


# ----------- Priority queue ----------------------
add_executable(test_priority_queue
        test_priority_queue.cpp
        ${CMAKE_SOURCE_DIR}/src/priority_queue/priority_queue.cpp
)
target_include_directories(test_priority_queue PRIVATE ${CMAKE_SOURCE_DIR}/src/priority_queue/)
target_compile_definitions(test_priority_queue PRIVATE TEST)


# ----------- Dijkstra  ----------------------
add_executable(test_dijkstra
        test_dijkstra.cpp
        ${CMAKE_SOURCE_DIR}/src/dijkstra/graph.cpp
)
target_include_directories(test_dijkstra PRIVATE ${CMAKE_SOURCE_DIR}/src/dijkstra/)
target_compile_definitions(test_dijkstra PRIVATE TEST)


# -------- TODO: добавить A* и Greedy first search ------