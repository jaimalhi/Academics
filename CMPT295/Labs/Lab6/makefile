SFLAGS = -S -O2
OFLAGS = -g -c
CFLAGS = -o x
	
all: x	

x: main.o qsorts.o 
	gcc $(CFLAGS) main.o qsorts.o

main.o:	main.s
	gcc $(OFLAGS) main.s

main.s:	main.c
	gcc $(SFLAGS)  main.c

qsorts.o: qsorts.s
	gcc $(OFLAGS) qsorts.s

qsorts.s: qsorts.c
	gcc $(SFLAGS) qsorts.c

clean:	
	rm -f x *.o   # rm -f *.o *.s x
