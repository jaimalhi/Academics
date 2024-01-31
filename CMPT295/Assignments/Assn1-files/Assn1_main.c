/* 
 * Filename: Assn1_main.c
 *
 * Description: Test driver for Assn1_Q3.c
 *
 * Author: Anne Lavergne + Jai Malhi
 * Student number: 301457742
 */
 
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer, size_t);
void show_bytes_2(byte_pointer, size_t);
void show_bits(int);
void show_int(int);
void show_float(float);
void show_pointer(void *);
int  mask_LSbits(int);

int main() {
    int ival = 12345;
    float fval = (float) ival;
    int *pval = &ival;

    show_int(ival);
    show_float(fval);
    show_pointer(pval);

    /* Add your test cases here in order
    to test the functions you have modified 
    and the functions you have created. */
    show_bits(12345);
    printf("Mask return: %d\n",mask_LSbits(15));
    printf("Mask return: %d\n",mask_LSbits(2));
    printf("Mask return: %d\n",mask_LSbits(4));
    printf("Mask return: %d\n",mask_LSbits(0));
    return 0;
}