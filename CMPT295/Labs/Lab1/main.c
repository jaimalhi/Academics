/* 
 * Filename: main.c
 *
 * Description: Test driver for our Lab 1.
 *              Reads two values at the command line and call 
 *              times(...) using these values as its arguments.
 *
 * Auhtor:
 * Modification date: Jan. 2023
 */ 

#include <stdlib.h>  // atoi()
#include <stdio.h>   // printf()

int times(int, int);

int main(int argc, char *argv[]) {
  int a = 0;
  int b = 0;
  int answer = 0;

  if (argc == 3) {
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    answer = times(a, b);
    printf("times(%d, %d) produces %d as a result.\n", a, b, answer);
  } 
  else {
    printf("Must supply 2 integers.\n");
    return 1;
  }
  return 0;
}
