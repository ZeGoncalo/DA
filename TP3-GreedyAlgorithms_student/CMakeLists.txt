cmake_minimum_required(VERSION 3.26)
project(TP3_GreedyAlgorithms_student)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(TP3)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP})

add_executable(TP3_GreedyAlgorithms_student
        TP3/ex1.cpp
        data_structures/UFDS.cpp
        data_structures/UFDS.h
        TP3/ex2.cpp
        TP3/ex4.cpp
        TP3/ex3.cpp
        TP3/ex5.cpp
        TP3/ex6.cpp
)

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

target_link_libraries(TP3_GreedyAlgorithms_student gtest gtest_main gmock gmock_main)