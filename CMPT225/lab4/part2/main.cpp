//main.cpp
#include <iostream>
#include "Sequence.h"
using namespace std;


void print(Sequence<int> &S, ostream& os) {
    unsigned n = S.getSize();
    os << '[';
    for (unsigned i = 0; i < n; i++) {
        os << (i ? ", ": "") << S.get(i);
    }
    os << ']' << endl;
} // print


int main () {
    //Sequence S(5);
    Sequence<int> S(5);

    print(S, cout);

    for (int i = 0; i < 5; i++) {
        S.set(i, (i+1)*3);
    } // for

    print(S, cout);

    for (int i = 0; i < 5; i++) {
        S.append(i);
    } // for

    print(S, cout);

    S.trunc(3);

    print(S, cout);

    return 0;
} // main

