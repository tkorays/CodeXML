cmake_minimum_required(VERSION 3.3)
project(invoker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 3rdparty/tinyxml2/tinyxml2.cpp src/proc.cpp proc_test.cpp src/proc_base_func.h src/proc_base_func.cpp v1/memory.h v1/memory.cpp)
add_executable(invoker ${SOURCE_FILES})