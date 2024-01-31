## makefile for Assignment 3, Question 3 of CMPT-295 (Spring 2023)
#Author: Jai Malhi
#flags taken from lec11-demo makefle

########### Compile w Assembly ###########
SFLAGS = -S -O1
OFLAGS = -g -c
CFLAGS = -o q3

#Linking
q3: decode2.o
	gcc $(CFLAGS) decode2.o 

#Assembling
decode2.o:	decode2.s
	gcc $(OFLAGS) decode2.s

#Compiling
decode2.s:	decode2.c
	gcc $(SFLAGS) decode2.c
 
#change to { rm -f q3 *.o } if you want to keep decode2.s when cleaning
clean:
	rm -f q3 decode2.s *.o

########### Compile w/o Assembly ###########
# a3q3: decode2.c 
# 	gcc -g -o a3q3 decode2.c 

# clean:	
# 	rm -f a3q3 *.o 

########### Compile in terminal ###########
# gcc -S -Og decode2.c
# gcc -c decode2.s
# gcc a3q3 decode2.o
# ./a3q3