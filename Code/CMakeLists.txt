cmake_minimum_required(VERSION 3.7)
project(Hw1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES smash.cpp commands.cpp commands.h signals.cpp signals.h)
add_executable(HwClion ${SOURCE_FILES})