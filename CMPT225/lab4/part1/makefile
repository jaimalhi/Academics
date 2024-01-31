
x:	main.o Sequence.o
	g++ -o x -Wall main.o Sequence.o

main.o:	main.cpp Sequence.h
	g++ -c -Wall main.cpp

Sequence.o:	Sequence.cpp Sequence.h
	g++ -c -Wall Sequence.cpp


clean:
	rm -f *.o x
