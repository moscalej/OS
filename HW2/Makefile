# Makefile for the smash program
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = Account.o AccountDataBase.o Atm.o Bank.o IOThreadSave.o
RM = rm -f
# Creating the  executable
Bank_sys: $(OBJS)
	$(CCLINK) -o main Args.h $(OBJS)
# Creating the object files
Atm.o: Atm.cpp Atm.h
Account.o: Account.cpp Account.h
AccountDataBase.o: AccountDataBase.cpp AccountDataBase.h
Bank.o: Bank.cpp Bank.h
IOThreadSave.o: IOThreadSave.cpp IOThreadSave.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* Bank_sys.*

