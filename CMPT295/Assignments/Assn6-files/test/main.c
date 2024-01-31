/*
 * Filename: main.c
 * Description: Main driver for matrix manipulating functions
 * Date: March 10, 2023
 * Name: Jai Malhi & Nyls Poonoosamy
 */

#include <stdio.h>   // printf()

#define N 4

void copy(void *, void *, int);
void transpose(void *, int );
void reverseColumns(void *, int n);
void printMatrixByRow(void *, int);

char A[N][N] = { 1,  -2,  3,  -4,
                -5,   6, -7,   8,
                -1,   2, -3,   4,
                 5,  -6,  7,  -8};

char C[N][N];

void main() {
    int i, j;

	printf("Matrix A: \n");
    printMatrixByRow(A, N); 
	
    printf("Copy A to C\n");
    copy(A, C, N);
	
	printf("\nMatrix C: \n");
    printMatrixByRow(C, N);

    printf("Rotating the matrix C by 90 degrees clockwise: \n");
    transpose(C, N);  
    reverseColumns(C, N);
    printMatrixByRow(C, N);

    return;
}

void printMatrixByRow(void *D, int n) {
    int i, j;
    char val;
    for (i = 0; i < n; i++) {
        val = *((char*)(D + i*n + j));
        printf("%4d %4d %4d %4d", *((char*)(D + i*n + 0)), *((char*)(D + i*n + 1)), *((char*)(D + i*n + 2)), *((char*)(D + i*n + 3)));
        printf("\n");
    }
    printf("\n");
}

//* Code for Transpose & reverseCols
void transpose(void *D, int n){
    char (*arr)[n] = (char (*)[n])D; // cast D to char (*)[n] pointer

    for(int row = 0; row < n; row++){
        for(int col = row; col < n; col++){
            char temp = arr[row][col];
            arr[row][col] = arr[col][row];
            arr[col][row] = temp;
        }
    }
}

void reverseColumns(void *D, int n){
    char (*arr)[n] = (char (*)[n])D; // cast D to char (*)[n] pointer

    for(int col = 0; col < n/2; col++){
        for(int row = 0; row < n; row++){
            char temp = arr[row][col];
            arr[row][col] = arr[row][n-col-1];
            arr[row][n-col-1] = temp;
        }
    }
}