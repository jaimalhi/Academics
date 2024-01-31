
#include "BST.h"
#include <iostream>
#include <string>
using namespace std;


int main () {
    BST S;

    int A[7] = {5, 8, 2, 3, 1, 9, 4};

    for (int i = 0; i < 7; i++) {
        S.insert(A[i]);
        S.print();
        string s;
        getline(cin, s);
    }

    S.print();

    return 0;

}

