# Chess Makefile based on
# https://www.softwaretestinghelp.com/cpp-makefile-tutorial/
 
# *****************************************************
# Variables to control Makefile operation

# Compiler 
CC = c++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
# CFLAGS =

# The build target 
TARGET = test

# Include files
INC = board.cc piece.cc 

# ****************************************************
# Targets needed to bring the executable up to date
all:
	$(CC) -o $(TARGET) test.cpp $(INC)

clean:
	rm $(TARGET)