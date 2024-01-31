
x:	main.o
	g++ -o x -Wall main.o

main.o:	main.cpp Sequence.h
	g++ -c -Wall main.cpp

test:	testmain.cpp Sequence.h
	g++ -o test -Wall testmain.cpp
	./test

clean:
	rm -f *.o x test
