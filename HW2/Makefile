# Makefile for the Bank
CC = g++
CFLAGS =  -g -std=c++0x -Wall
CCLINK = $(CC)
OBJS =  Account.o main.o AccountDataBase.o Atm.o IOThreadSave.o ThreadFunc.o
RM = rm -f
TARGET=Bank
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) $(CFLAGS) -o Bank $(OBJS) -lpthread
# Creating the object files
Account.o: Account.cpp Account.h
main.o: main.cpp ThreadFunc.h
Atm.o: Atm.cpp Atm.h
AccountDataBase.o: AccountDataBase.cpp AccountDataBase.h
IOThreadSave.o: IOThreadSave.cpp IOThreadSave.h
ThreadFunc.o: ThreadFunc.cpp ThreadFunc.h


# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* Bank1.*
