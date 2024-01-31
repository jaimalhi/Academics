//profile-ss.cpp
#include "ss.h"

//Function declarations
unsigned searchMin(int a[], unsigned len, unsigned& count);

// Desc: Sorts given array from least to greatest using recursion  
void ss(int a[], unsigned len, unsigned& count) {
    if (len <= 1 && count++) return;
    
    //minPos = index of minimum element in a[n]
    unsigned minPos = searchMin(a, len, count);
    count++;

    //Swap values 
    int tmp = a[0]; //temp = first value of array
    count++;

    a[0] = a[minPos]; //set a[0] = the minimum element in array
    count++;

    a[minPos] = tmp; //set a[minPos] = the previous a[0]
    count++;

    ss(a + 1, len - 1, count);
    count++;
} // ss

// Desc:  Finds the position of the minimum element in a[n]
//  Pre:  len > 0
// Post:  a[] elements are unchanged.
unsigned searchMin(int a[], unsigned len, unsigned& count) {
    unsigned ret = --len;
    count++;

    while (len-- && count++) {
        count++;
        if (a[len] < a[ret] && count++) {
            ret = len;
            count++;
        }
    }

    return ret;
} // searchMin



