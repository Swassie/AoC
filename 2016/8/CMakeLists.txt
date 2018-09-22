cmake_minimum_required(VERSION 3.6)
project(8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Display.cpp Display.h)
add_executable(8 ${SOURCE_FILES})