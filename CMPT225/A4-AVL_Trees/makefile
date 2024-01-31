#Makefile for Assignment 4 of CMPT 225, Summer 2022
CPPFLAGS = -std=c++17 -Wall -ggdb3 -Wextra -Wnon-virtual-dtor

#Call 'make' to create .o files, run with ./x
#call 'make main' to create .o files for main.cpp, run with ./z
x: a4main.o 
	g++ -o x $(CPPFLAGS) a4main.o

a4main.o: a4main.cpp AVLTree.h
	g++ -c $(CPPFLAGS) a4main.cpp

z: maintest.o
	g++ -o z $(CPPFLAGS) maintest.cpp 

maintest.o: maintest.cpp AVLTree.h
	g++ -c $(CPPFLAGS) maintest.cpp

clean: 
	rm -f x z *.o