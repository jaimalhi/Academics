# ======================== Compiler flags ========================
# -std=c99: This flag tells the compiler to adhere to the C* standard 
# 		of the C language. This is a specific version of the C 
#		language standard.
# -Wall: This flag enables all the warnings about constructions that 
# 		some users consider questionable, and that are easy to avoid.
# -ggdb3: This flag produces debugging information in the operating
# 		system's native format (stabs, COFF, XCOFF, or DWARF 2). GDB 
#		can work with this debugging information. The '3' is a level 
# 		of detail for the debugging information.
# -Wextra: This flag enables some extra warning flags that are not 
# 		enabled by -Wall.
# -Werror: This flag makes all warnings into errors. With this flag, 
# 		the compiler will stop at the first warning it encounters.
# -Wfatal-errors: This flag makes all errors that would be reported 
# 		as warnings and stops after encountering one.
# -g: This flag is a general flag that tells the compiler to include
# 		information for debugging in the output file.
# -Wno-error=unused-parameter: This flag turns off the -Werror flag 
# 		specifically for the unused-parameter warning. This means that 
#		if a function parameter is not used, it will not be treated as 
# 		an error and stop the compilation.
# -Wno-unused-parameter: 
#		This flag turns off the -Wunused-parameter
# -lpthread: This flag links the pthread library to the program. 
#		The pthread library is used for multithreading in C.
# ======================== Compiler flags ========================
# CFLAGS = -std=c11 -g -Wall -Werror -ggdb3 -Wextra -Wno-unused-parameter
CFLAGS = -std=c99 -g -Wall -Werror -ggdb3

all: build

build:
	gcc $(CFLAGS) main.c -o main

run: build
	./main

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main *.o


