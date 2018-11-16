cmake_minimum_required(VERSION 3.12)
project(ProgrammingCourseWork)

set(CMAKE_CXX_STANDARD 14)

add_executable(Btree binaryTree/binarySearch.cpp)
add_executable(Graph graph/binarySearch.h "graph/graph.cpp")