/***
 *
 * Testing driver for class Triple
 *
 **/

//g++ -Wall -o x main.cpp Triple.cpp

#include <iostream>
#include "Triple.h"

using namespace std;


int main () {
    // testing from Lab 1
    Triple A(12.0, 4.6, 6.0);
    Triple B(14.2, -3.0, 11.4);

    cout << "Lab 1 Tests:" << endl;

    cout << "A = "; print(A); cout << endl;
    cout << "B = "; print(B); cout << endl;

    cout << "B = " << B << endl;

    Triple C(2.7, -3.5, -0.6);

    cout << "C = "; print(C); cout << endl;

    cout << "A·B = " << dotProduct(A,B) << endl;
    cout << "A·C = " << dotProduct(A,C) << endl;
    cout << "B·C = " << dotProduct(B,C) << endl;

    cout << endl;


    // testing for Lab 2
    cout << "Lab 2 Tests:" << endl;

    cout << "A·B = " << A * B << endl;
    cout << "A·C = " << A * C << endl;
    cout << "B·C = " << B * C << endl;
    cout << endl;

    cout << "A+B = "; print(A + B); cout << endl;
    cout << "A+C = "; print(A + C); cout << endl;
    cout << "B+C = "; print(B + C); cout << endl;
    cout << endl;

    Triple D;
    D = A;
    cout << "A+B = "; print(D += B); cout << endl;
    D = A;
    cout << "A+C = "; print(D += C); cout << endl;
    D = B;
    cout << "B+C = "; print(D += C); cout << endl;

} // main

