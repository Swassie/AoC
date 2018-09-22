cmake_minimum_required(VERSION 3.6)
project(22)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.cpp Node.h State.cpp State.h)
add_executable(22 ${SOURCE_FILES})