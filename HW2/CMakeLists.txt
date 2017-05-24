cmake_minimum_required(VERSION 3.7)
project(HW2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Account.h data_base_accounts.cpp data_base_accounts.h Atm.cpp Atm.h Bank.cpp Bank.h VectorWR.cpp VectorWR.h Account.cpp)
add_executable(HW2 ${SOURCE_FILES})