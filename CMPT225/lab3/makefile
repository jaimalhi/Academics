
x:	main.o Sequence.o
	g++ -o x -Wall -Wfatal-errors main.o Sequence.o

main.o:	main.cpp Sequence.h
	g++ -c -Wall -Wfatal-errors main.cpp

Sequence.o:	Sequence.cpp Sequence.h
	g++ -c -Wall -Wfatal-errors Sequence.cpp


clean:
	rm -f *.o x
