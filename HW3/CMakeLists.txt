cmake_minimum_required(VERSION 3.7)
project(HW3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Code/PhysMem.cpp Code/PhysMem.h Code/SwapDevice.cpp Code/SwapDevice.h Code/testProg1.cpp Code/VirtualMemory.cpp Code/VirtualMemory.h Code/OurPointer.cpp Code/OurPointer.h Code/PageTable.cpp Code/PageTable.h Code/PageDirectoryEntry.cpp Code/PageDirectoryEntry.h Code/PageTableEntry.cpp Code/PageTableEntry.h Code/HelpFunc.h)
add_executable(HW3 ${SOURCE_FILES})