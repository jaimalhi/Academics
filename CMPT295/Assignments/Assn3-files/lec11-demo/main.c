/*
 * Filename: main.c
 *
 * Purpose: Demo during Lecture 11
 * 
 * Date: Jan. 2023
 *
*/

#include <stdio.h>

long arith(long x, long y, long z);

long globalA;

int main( ) {

// Test Case 1 - Expected result = 1350
	long x = 2;
	long y = 3;
	long z = 4;

	long result = arith(x, y, z);
	printf("x = %ld, y = %ld, z = %ld and result of arith is %ld\n", x, y, z, result);

	globalA = result;

// Test Case 2 - Expected result = 386
 	x = -3;
	y = 4;
	z = 1;

	result = arith(x, y, z);
	printf("x = %ld, y = %ld, z = %ld and result of arith is %ld\n", x, y, z, result);
 
    return 0;
}
