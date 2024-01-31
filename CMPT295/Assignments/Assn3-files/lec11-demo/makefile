SFLAGS = -S -O1
OFLAGS = -g -c
CFLAGS = -o ar

# Linking
ar: main.o arith.o
	gcc $(CFLAGS) arith.o main.o 

# Assembling
main.o:	main.s
	gcc $(OFLAGS) main.s

arith.o: arith.s
	gcc $(OFLAGS) arith.s

# Compiling
main.s:	main.c
	gcc $(SFLAGS) main.c

# Comment out these lines when we write our own assembly program (i.e., arith.s)
# arith.s: arith.c
#	gcc $(SFLAGS) arith.c

clean:
	rm -f ar *.o