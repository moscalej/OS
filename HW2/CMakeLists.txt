cmake_minimum_required(VERSION 3.7)
project(HW2)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Account.cpp Account.h AccountDataBase.cpp AccountDataBase.h Atm.cpp Atm.h IOThreadSave.cpp IOThreadSave.h ThreadFunc.cpp ThreadFunc.h)
add_executable(HW2 ${SOURCE_FILES})