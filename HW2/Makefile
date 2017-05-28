# Makefile for the Bank
CC = g++
CFLAGS = -std=c++0x -g -Wall
CCLINK = $(CC)
OBJS =  Account.o main.o AccountDataBase.o Bank.o Atm.o IOThreadSave.o
RM = rm -f
TARGET=Bank1
# Creating the  executable
Bank1: $(OBJS)
	$(CCLINK) $(CFLAGS) -o Bank1 $(OBJS)
# Creating the object files
Account.o: Account.cpp Account.h
main.o: main.cpp Args.h
Atm.o: Atm.cpp Atm.h
Bank.o: Bank.cpp Bank.h
AccountDataBase.o: AccountDataBase.cpp AccountDataBase.h
IOThreadSave.o: IOThreadSave.cpp IOThreadSave.h


# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* Bank1.*

