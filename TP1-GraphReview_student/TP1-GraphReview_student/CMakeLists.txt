cmake_minimum_required(VERSION 3.22.1)
project(TP1_GraphReview_student)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Debug" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(TP1)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(TP1_GraphReview_student
        TP1/ex1.cpp
        TP1/ex2.cpp
        TP1/ex3.cpp
        TP1/ex4.cpp
        TP1/ex5.cpp
        data_structures/createGraphs.cpp
        data_structures/createGraphs.h)

target_link_libraries(TP1_GraphReview_student gtest gtest_main gmock gmock_main)
