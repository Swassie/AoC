cmake_minimum_required(VERSION 3.6)
project(14)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp md5.cpp md5.h)
add_executable(14 ${SOURCE_FILES})