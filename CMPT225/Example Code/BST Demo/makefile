x:	 testBST.o BST.o
	g++ -o x testBST.o BST.o

testBST.o:	 testBST.cpp BST.h
	g++ -c testBST.cpp

BST.o:	 BST.cpp BST.h
	g++ -c BST.cpp

clean:	
	rm -f core *.o x


