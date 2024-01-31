
#include <iostream>
#include <string>
#include "Sequence.h"
using namespace std;


void print(Sequence<string> &S, ostream& os) {
    unsigned n = S.getSize();
    os << '[';
    for (unsigned i = 0; i < n; i++) {
        os << (i ? ", ": "") << S.get(i);
    }
    os << ']' << endl;
} // print


int main () {
    Sequence<string> S(5);

    print(S, cout);

    S.set(0, "zero");
    S.set(1, "three");
    S.set(2, "six");
    S.set(3, "nine");
    S.set(4, "twelve");

    print(S, cout);

    S.append("zero");
    S.append("one");
    S.append("two");
    S.append("three");
    S.append("four");

    print(S, cout);

    S.trunc(3);

    print(S, cout);

    return 0;
} // main

