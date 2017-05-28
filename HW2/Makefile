# Makefile for the Bank
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = main.o Bank.o Account.o Atm.o IOThreadSave.o AccountDataBase.o
RM = rm -f
TARGET=Bank
# Creating the  executable
Bank1: $(OBJS)
	$(CCLINK) -o Bank $(OBJS) -lpthread
# Creating the object files
account.o: Account.c Account.h
main.o: main.cpp Args.h
Atm.o: Atm.cpp Atm.h
Bank.o: Bank.cpp Bank.h
AccountDataBase.o: AccountDataBase.cpp AccountDataBase.h
IOThreadSave.o: IOThreadSave.cpp IOThreadSave.h


# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* Bank1.*

