# Compiler flags
CFLAGS = -std=c11 -Wall -ggdb3 -Wextra -Werror -Wfatal-errors -g -Wno-error=unused-parameter

# Executable names
sockets: sockets.o
	gcc -o s sockets.o

args: takeArgs.o
	gcc -o args takeArgs.o

# Compile the source files
sockets.o: sockets.c
	gcc -c $(CFLAGS) sockets.c

takeArgs.o: takeArgs.c
	gcc -c $(CFLAGS) takeArgs.c

# Clean up
clean:
	rm -f t s args sockets *.o


