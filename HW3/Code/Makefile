CCC = g++ 
CXXFLAGS = -Wall -g  -std=c++0x
# pavel removed the pthread flag
CXXLINK = $(CCC)
OBJS = main.o OurPointer.o PageTable.o PageDirectoryEntry.o PageTableEntry.o VirtualMemory.o PhysMem.o SwapDevice.o HelpFunc.o
RM = rm -f
# Creating the  executable
main: $(OBJS)
	$(CXXLINK) -o main $(CXXFLAGS) $(OBJS)
# Creating the object files
main.o: main.cpp VirtualMemory.h
OurPointer.o: OurPointer.cpp OurPointer.h VirtualMemory.h
PageTable.o: PageTable.cpp PageTable.h 
PageDirectoryEntry.o: PageDirectoryEntry.cpp PageDirectoryEntry.h
PageTableEntry.o: PageTableEntry.cpp PageTableEntry.h
VirtualMemory.o: VirtualMemory.cpp VirtualMemory.h OurPointer.h
SwapDevice.o: SwapDevice.cpp SwapDevice.h 
PhysMem.o: PhysMem.cpp PhysMem.h
HelpFunc.o: HelpFunc.cpp HelpFunc.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"*