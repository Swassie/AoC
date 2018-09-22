cmake_minimum_required(VERSION 3.6)
project(24)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp State.cpp State.h)
add_executable(24 ${SOURCE_FILES})