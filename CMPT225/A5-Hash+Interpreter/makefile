#Makefile for Assignment 5 of CMPT 225, summer 2022
CPPFLAGS = -std=c++11 -Wall -ggdb3 -Wextra -Wnon-virtual-dtor

all:	 hashdemo pish setdemo testParse testScanner

hashdemo:	 hashdemo.o
	g++ $(CPPFLAGS) -o hashdemo hashdemo.o

pish:	 pish.o Scanner.o Parse.o
	g++ $(CPPFLAGS) -o pish pish.o Scanner.o Parse.o

setdemo:	 setdemo.o
	g++ $(CPPFLAGS) -o setdemo setdemo.o

testParse:	 testParse.o Scanner.o Parse.o
	g++ $(CPPFLAGS) -o testParse testParse.o Scanner.o Parse.o

testScanner:	 testScanner.o Scanner.o
	g++ $(CPPFLAGS) -o testScanner testScanner.o Scanner.o

hashdemo.o:	 hashdemo.cpp hash.h
	g++ $(CPPFLAGS) -c hashdemo.cpp

pish.o:	 pish.cpp hash.h Scanner.h Parse.h
	g++ $(CPPFLAGS) -c pish.cpp

Scanner.o:	 Scanner.cpp Scanner.h
	g++ $(CPPFLAGS) -c Scanner.cpp

Parse.o:	 Parse.cpp Parse.h
	g++ $(CPPFLAGS) -c Parse.cpp

setdemo.o:	 setdemo.cpp set.h
	g++ $(CPPFLAGS) -c setdemo.cpp

testParse.o:	 testParse.cpp Scanner.h Parse.h
	g++ $(CPPFLAGS) -c testParse.cpp

testScanner.o:	 testScanner.cpp Scanner.h
	g++ $(CPPFLAGS) -c testScanner.cpp

clean:	
	rm -f core *.o hashdemo pish setdemo testParse testScanner


