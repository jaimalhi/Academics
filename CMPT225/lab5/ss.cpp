//ss.cpp
#include "ss.h"

unsigned searchMin(int a[], unsigned len);

// Desc: Sorts given array from least to greatest using recursion  
void ss(int a[], unsigned len) {
    if (len <= 1) return;

    //minPos = index of minimum element in a[n]
    unsigned minPos = searchMin(a, len);

    //Swap values 
    int tmp = a[0]; //temp = first value of array
    a[0] = a[minPos]; //set a[0] = the minimum element in array
    a[minPos] = tmp; //set a[minPos] = the previous a[0]

    ss(a + 1, len - 1);
} // ss

// Desc:  Finds the position of the minimum element in a[n]
//  Pre:  len > 0
// Post:  a[] elements are unchanged.
unsigned searchMin(int a[], unsigned len) {
    unsigned ret = --len;

    while (len--) {
        if (a[len] < a[ret]) {
            ret = len;
        }
    }

    return ret;
} // searchMax



