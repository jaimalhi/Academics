#include <iostream>
#include <cmath>
#include <ios>
using namespace std;

int main()
{
    //Info
    int end = 0;
    cout << fixed;

    //While number is outside desired range
    while (end < 1 || end > 213)
    {
        //User Input
        cout << "Enter end of sequence, between 1 and 213: ";
        cin >> end;
        cout << endl;
    }

    //Print Titles
    cout << setw(3) << "x" << setw(9) << "sqrt(x)" << setw(7) << "x^2" << setw(8) << "x^3" << endl;

    //Print square root, square and cube of numbers 1 to 10
    for (int x = 1; x <= end; ++x)
    {
        cout << setw(3) << x << setw(8);
        //Square root
        cout.precision(3);
        cout << setw(8) << sqrt(x) << setw(8);
        //Square and cube
        cout.precision(0);
        cout << setw(8) << pow(x, 2) << setw(8);
        cout << pow(x, 3);
        cout << endl;
    }

    return 0;
}
