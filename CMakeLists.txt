cmake_minimum_required(VERSION 3.12)
project(ProgrammingCourseWork)

set(CMAKE_CXX_STANDARD 14)

add_executable(treeTesting "unitTesting/testingTree.cpp" main/graph.h main/binarySearch.h)
add_executable(graphTesting "unitTesting/graphTesting.cpp" main/graph.h main/binarySearch.h)
add_executable(generalTest "unitTesting/testFile.cpp" main/graph.h main/binarySearch.h)

