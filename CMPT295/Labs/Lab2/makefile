runtest: main.o subprog.o 
	gcc -o runtest subprog.o main.o -Wall

main.o: main.c
	gcc -g -c main.c
	
subprog.o: subprog.c
	gcc -g -c subprog.c
	
clean: 
	rm -f runtest *.o
