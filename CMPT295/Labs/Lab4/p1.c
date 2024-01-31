/* 
 * Filename: p1.c
 *
 * Description: p1.c for our Lab 4.
 *
 * Auhtor:
 * Modification date: Feb. 2023
 */
 
#include <stdio.h>

int proc2(int, int);

//a = 6, b = 9 
void proc1(char *s, int *a, int *b) {
    int v;
    int t;

    t = *a;
    v = proc2(*a, *b); //v = 42

    sprintf(s, "The result of proc2(%d,%d) is %d.", *a, *b, v);

    *a = *b - 2; //a = 9-2 = 7
    *b = t; //b = t = 6 

    return;
}
