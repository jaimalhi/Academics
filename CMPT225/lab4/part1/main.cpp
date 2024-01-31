//Part 1
#include "Sequence.h"
#include <iostream>
#include <vector>
using namespace std;

void print(vector<int> &S, ostream& os) {
    unsigned n = S.size();
    os << '[';
    for (unsigned i = 0; i < n; i++) {
        os << (i ? ", ": "") << S[i];
    }
    os << ']' << endl;
} // print


int main () {
    //Sequence S(5);
    vector<int> S(5);

    print(S, cout);

    for (int i = 0; i < 5; i++) {
        S[i] = (i+1)*3;
        //S.set(i, (i+1)*3);
    } // for

    print(S, cout);

    for (int i = 0; i < 5; i++) {
        S.push_back(i);
        //S.append(i);
    } // for

    print(S, cout);

    S.resize(3); //is this correct?
    //S.trunc(3);

    print(S, cout);

    return 0;
} // main

// void print(Sequence &S, ostream& os) {
//     unsigned n = S.getSize();
//     os << '[';
//     for (unsigned i = 0; i < n; i++) {
//         os << (i ? ", ": "") << S.get(i);
//     }
//     os << ']' << endl;
// } // print with Sequence