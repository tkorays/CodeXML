cmake_minimum_required(VERSION 3.3)
project(PcapReader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PcapReader.h DataParser.h DataParser.cpp)
add_executable(PcapReader ${SOURCE_FILES})