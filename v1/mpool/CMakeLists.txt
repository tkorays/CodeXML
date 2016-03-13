cmake_minimum_required(VERSION 3.3)
project(mpool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp mpool.cpp)
add_executable(mpool ${SOURCE_FILES})