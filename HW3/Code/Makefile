# Makefile for the Bank
CC = g++
CFLAGS =  -g -std=c++0x -Wall
CCLINK = $(CC)
OBJS =  PhysMem.o SwapDevice.o testProg1.o VirtualMemory.o OurPointer.o PageTable.o PageDirectoryEntry.o PageTableEntry.o HelpFunc.o

RM = rm -f
TARGET=testProg
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) $(CFLAGS) -o testProg $(OBJS) -lpthread
# Creating the object files

testProg1.o: VirtualMemory.h
PhysMem.o: PhysMem.cpp PhysMem.h
SwapDevice.o: SwapDevice.cpp SwapDevice.h
VirtualMemory.o: VirtualMemory.cpp VirtualMemory.h
OurPointer.o: OurPointer.cpp OurPointer.h
PageTable.o:  PageTable.cpp  PageTable.h
PageDirectoryEntry.o: PageDirectoryEntry.cpp PageDirectoryEntry.h
PageTableEntry.o: PageTableEntry.cpp PageTableEntry.h
HelpFunc.o: HelpFunc.cpp HelpFunc.h


# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* testProg.*
