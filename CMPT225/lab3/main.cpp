//Main.cpp
#include <iostream>
#include <stdexcept>
#include "Sequence.h"


using namespace std;

int main () {
    Sequence S(5);

    S.print(cout);

    for (int i = 0; i < 5; i++) {
        S.set(i, (i+1)*3);
    } // for

    S.print(cout);

    try {
        for (int i = 0; i < 7; i++) {
            cout << S.get(i) << ' ';
        } // for
    }
    catch(exception& e) {
        cout << "\nException occurred: " << e.what() << endl;
    }

    return 0;
} // main

