
#include <iostream>
#include "Sequence.h"


using namespace std;

int main () {
    Sequence S;

    // S.print(cout);
    for (int i = 0; i < 5; i++) {
        S.append(i*3);
        // S.print(cout);
    } // for

    /*
    for (int i = 0; i < 8; i++) {
        S.set(i, 10-i);
        S.print(cout);
    } // for
    */

    /*
    for (int i = 0; i < 5; i++) {
        S.insert(2*i, i*i);
        S.print(cout);
    }
    */

    return 0;
} // main

