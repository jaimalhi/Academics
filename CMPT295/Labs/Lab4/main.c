/* 
 * Filename: main.c
 *
 * Description: Test driver for our Lab 4.
 *
 * Auhtor:
 * Modification date: Feb. 2023
 */

#include <stdio.h>

void proc1(char *, int *, int *);

void main() {
    char buf[40];
    int x = 6;
    int y = 9;
    
    printf("Original values are: x=%d, y=%d.\n", x, y); //x = 6, y = 9
    proc1(buf, &x, &y);
    printf("Final values are: x=%d, y=%d.\n", x, y); //x = 7, y = 6
    puts(buf);
    return;
}

