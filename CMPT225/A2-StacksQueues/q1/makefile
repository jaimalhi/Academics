#makefile for Assignment 2, question 1 for CMPT 225 (Summer 2022)

# Set the C++ compiler options:
CPPFLAGS = -std=c++11 -Wall -ggdb3 -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

# call ./stacks to run code
stacks: Stack.o StkTest.o
	g++ -o stacks Stack.o StkTest.o 

Stack: 
	g++ -c $(CPPFLAGS) Stack.cpp

StkTest: 
	g++ -c $(CPPFLAGS) StkTest.cpp

clean:
	rm -f stacks Stack.o StkTest.o