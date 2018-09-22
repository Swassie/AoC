cmake_minimum_required(VERSION 3.6)
project(10)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Bot.cpp Bot.h IMicrochipHandler.h Bin.cpp Bin.h)
add_executable(10 ${SOURCE_FILES})