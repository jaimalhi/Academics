#makefile Instructions:
#call 'make' to create .o files for main.cpp, run with ./x
#call 'make test' to create .o files for test_queue.cpp, run with ./test
x:	Queue.o main.o
	g++ -o x -Wall -ggdb3 Queue.o main.o

Queue.o:	Queue.cpp Queue.h
	g++ -c -Wall -ggdb3 Queue.cpp

main.o:	main.cpp Queue.h
	g++ -c -Wall -ggdb3 main.cpp

test: Queue.o test_queue.o
	g++ -o test -Wall -ggdb3 Queue.o test_queue.o

test_queue.o: test_queue.cpp Queue.h
	g++ -c -Wall -ggdb3 test_queue.cpp

clean:	
	rm -f x test *.o


