/*
 * Filename: main.c
 *
 * Purpose: Lab 2
 * 
 * Last Modified: Jan. 2023
 *
 */
 
#include <stdio.h>

typedef unsigned short bit16;

void mystery(bit16, char*);

void main() {
    bit16 x = 0x1234;
    char *someStr;
    char msg[16] = "The result is:";

    puts(msg);
    mystery(x, someStr);
    puts(someStr);

    return;
}
