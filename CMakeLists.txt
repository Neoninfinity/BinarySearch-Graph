cmake_minimum_required(VERSION 3.12)
project(ProgrammingCourseWork)

set(CMAKE_CXX_STANDARD 14)

add_executable(unitTesting "unitTesting/testing.cpp" graph/graph.h graph/binarySearch.h)
