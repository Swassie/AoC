cmake_minimum_required(VERSION 3.6)
project(11)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp State.cpp State.h)
add_executable(11 ${SOURCE_FILES})