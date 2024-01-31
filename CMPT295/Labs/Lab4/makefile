SFLAGS = -S -O2
OFLAGS = -g -c
CFLAGS = -o x

x:	main.o p1.o p2.o
	gcc $(CFLAGS) main.o p1.o p2.o

main.o:	main.s
	gcc $(OFLAGS) main.s

p1.o:	p1.s
	gcc $(OFLAGS) p1.s

p2.o:	p2.s
	gcc $(OFLAGS) p2.s

main.s:	main.c
	gcc $(SFLAGS) main.c

p1.s:	p1.c
	gcc $(SFLAGS) p1.c

p2.s:	p2.c
	gcc $(SFLAGS) p2.c

clean:	
	rm -f x *.o *.s

