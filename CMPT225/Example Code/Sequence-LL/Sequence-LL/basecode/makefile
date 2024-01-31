
x:	main.o Sequence.o
	gcc -o x -Wfatal-errors -lstdc++ main.o Sequence.o

main.o:	main.cpp Sequence.h
	gcc -c -Wfatal-errors main.cpp

Sequence.o:	Sequence.cpp Sequence.h
	gcc -c -Wfatal-errors Sequence.cpp


clean:
	rm -f *.o x
