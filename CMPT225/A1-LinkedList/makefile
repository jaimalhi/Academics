#######################################################################
# Makefile for Assignment 1 for CMPT 225 (D100), Summer 2022
#	make: Build the executable program a1
#
#	make -j: Build a1 possibly a little more quickly. The "-j" option tells make to 
#	try to use multiple CPUs when compiling two, or more files.
#
#	make clean: Delete a1, and all the .o object files.
#
#   make <name>: Compiles a specific file, where <name> is the name of
#      			 one of the rules listed in the makefile below
#######################################################################
# Set the C++ compiler options:
#   -std=c++17 compiles using the C++17 standard (or at least as 
#    much as is implemented by the compiler, e.g. for g++ see
#    http://gcc.gnu.org/projects/cxx0x.html)
#   -Wall turns on all warnings
#   -ggdb3 get line-by-line details for valgrind leaks
#   -Wextra turns on even more warnings
#   -Werror causes warnings to be errors 
#   -Wfatal-errors stops the compiler after the first error
#   -Wno-sign-compare turns off warnings for comparing signed and 
#    unsigned numbers
#   -Wnon-virtual-dtor warns about non-virtual destructors
#   -g puts debugging info into the executables (makes them larger)
CPPFLAGS = -std=c++11 -Wall -ggdb3 -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

######################################################
#call ./a1 to run the program (executable name)
a1: a1main.o PlayList.o Song.o
	g++ -o a1 a1main.o PlayList.o Song.o

a1main: 
	g++ -c $(CPPFLAGS) a1main.cpp

PlayList:
	g++ -c $(CPPFLAGS) PlayList.cpp

Song:
	g++ -c $(CPPFLAGS) Song.cpp

clean:
	rm -f a1 a1main.o PlayList.o Song.o
######################################################
#call ./Testing to run the program (executable name)
# Testing: TestFile.o PlayList.o Song.o
# 	g++ -o Testing TestFile.o PlayList.o Song.o

# TestFile: 
# 	g++ -c $(CPPFLAGS) TestFile.cpp

# Playlist: 
# 	g++ -c $(CPPFLAGS) PlayList.cpp

# Song:
# 	g++ -c $(CPPFLAGS) Song.cpp

# clean:
# 	rm -f Testing TestFile.o PlayList.o Song.o
######################################################