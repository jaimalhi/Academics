#Makefile for Assignment 3 of CMPT 225, Summer 2022
CPPFLAGS = -std=c++11 -Wall -ggdb3 -Wextra -Wnon-virtual-dtor

#Call 'make' to create .o files, run with ./x
x: main.o 
	g++ -o x main.o

main: main.cpp a3.h
	g++ -c $(CPPFLAGS) main.cpp

clean:
	rm -f x main.o