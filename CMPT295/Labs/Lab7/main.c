/* 
 * Filename: main.c
 *
 * Description: Microbenchmark driver for our Lab 7.
 *
 * Auhtor:
 * Modification date: April 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

//#include <sys/types.h>
//#include <sys/times.h>
//#include <sys/time.h>

int sumPlus(int *A, int n);

#define N 100
#define NTESTS 20

int A[N];
int P;
int Q;
int cycles[NTESTS];
long total;
int start_time = 150;
int end_time = 125;

void main () {
    srand(time(NULL));
    int i;
    struct rusage start;
    struct rusage end;

    // Init list
    Q = 0;
    for (i = 0; i < N; i++) {
        A[i] = rand() % 1024 - 512;
        if (A[i] > 0) Q += A[i];
    }

    // Run tests
    for (i = 0; i < NTESTS; i++) {
        getrusage(RUSAGE_SELF, &start);
        P = sumPlus(A, N);
        getrusage(RUSAGE_SELF, &end);
        cycles[i] = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) * 1000000 + (end.ru_utime.tv_usec - start.ru_utime.tv_usec);

        if (P != Q) {
            perror("Error:  sum mismatch"); return;
        }
    }

    // Display results
    total = 0;
    for (i = 0; i < NTESTS; i++) {
        printf("Sample %d completed in %d clock cycles.\n", i+1, cycles[i]);
        total += cycles[i];
    }
    printf("Average of %ld clock cycles.\n", total/NTESTS);

    return;
}
