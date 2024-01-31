
x:	main.o ss.o
	g++ -o x -Wall main.o ss.o

main.o:	main.cpp ss.h
	g++ -c -Wall main.cpp

ss.o:	ss.cpp ss.h
	g++ -c -Wall ss.cpp

profile-x:	profile-main.o profile-ss.o
	g++ -o profile-x -Wall profile-main.o profile-ss.o

profile-main.o:	profile-main.cpp profile-ss.h
	g++ -c -Wall profile-main.cpp

profile-ss.o:	profile-ss.cpp profile-ss.h
	g++ -c -Wall profile-ss.cpp

clean:
	rm -f *.o x profile-x
