# Makefile for the Bank
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = main.o Bank.o Account.o Atm.o IOThreadSave.o AccountDataBase.o
RM = rm -f
TARGET=Bank
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) -o Bank $(OBJS) -lpthread
# Creating the object files
account.o: account.c account.h mytypes.h
main.o: main.cpp Args.h
Atm.o: Atm.cpp Atm.h
Bank.o: Bank.cpp Bank.h
AccountDataBase.o AccountDataBase.cpp
IOThreadSave.o: IOThreadSave.cpp IOThreadSave.h


# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* Bank.*

