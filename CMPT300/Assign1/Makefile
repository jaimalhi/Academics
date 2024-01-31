# Compiler flags
CFLAGS = -std=c11 -Wall -ggdb3 -Wextra -Werror -Wfatal-errors -g -Wno-error=unused-parameter

# Executable name
a1: list.o main.o
	gcc -o a1 list.o main.o

# Compile list.o
list.o: list.c list.h
	gcc -c $(CFLAGS) list.c

# Compile list.o
main.o: main.c list.h
	gcc -c $(CFLAGS) main.c

# Clean up
clean:
	rm -f a1 *.o


