cmake_minimum_required(VERSION 3.3)
project(xml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp xxml.cpp)
add_executable(xml ${SOURCE_FILES})