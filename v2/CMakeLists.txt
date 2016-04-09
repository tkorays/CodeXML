cmake_minimum_required(VERSION 3.3)
project(codexml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES plugin_test.c plugin_if.h plugin.h plugin.c plugin_osx_adp.c plugin_adp.h)
add_executable(codexml ${SOURCE_FILES})