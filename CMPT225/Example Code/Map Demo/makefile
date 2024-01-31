
x:	main.o Triple.o
	g++ -o x main.o Triple.o

main.o:	main.cpp Triple.h
	g++ -c -std=c++11 -Wfatal-errors main.cpp

Triple.o:	Triple.cpp Triple.h
	g++ -c -std=c++11 -Wfatal-errors Triple.cpp

clean:	
	rm -f *.o x a.out
