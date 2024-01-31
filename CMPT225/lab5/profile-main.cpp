//profile-main.cpp
#include <iostream>
#include "profile-ss.h"


using namespace std;

int main () {
    int a[10] = { 4, 6, 10, 5, 1, 3, 8, 7, 2, 9 };
    //int a[10] = {10,1,2,3,4,5,6,7,8,9};
    
    unsigned counter = 0;

    ss(a, 10, counter);

    cout << "Operation count: " << counter << endl;

    return 0;
} // main

