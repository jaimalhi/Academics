/***
 *
 * Testing driver for class Triple
 *
 **/


#include <iostream>
#include <map>
#include "Triple.h"

using namespace std;


int main () {
    //
    // testing from Lab 1
    //

    // map <Triple, int> myMap;  // uses overloaded <
    map <Triple, int, TripleLess> myMap;

    Triple A(12.0, 4.6, 0.0);
    myMap[A] = 1;

    Triple B(14.2, 0.0, 11.4);
    myMap[B] = 1;

    Triple C(0.0, -3.5, -0.6);
    myMap[C] = 1;

    Triple D;
    
    D = A; D += B;
    myMap[D] = 1;
    D = A; D += C;
    myMap[D] = 1;
    D = B; D += C;
    myMap[D] = 1;

    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        cout << it->first << endl;
    }
} // main

