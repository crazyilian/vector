cmake_minimum_required(VERSION 3.29)
project(vector)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(cmake/BuildFlags.cmake)
include(cmake/TestSolution.cmake)

find_package(Catch REQUIRED)

add_catch(test_vector vector/test.cpp  vector/vector.hpp)
