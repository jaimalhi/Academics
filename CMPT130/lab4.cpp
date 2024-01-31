#include <iostream>
#include <ios>
using namespace std;

int main()
{
    //ios setting
    cout << fixed;
    cout.precision(8);
    //Ascending 1 to 10
    for(int i = 1; i <= 10; i++){
        cout << i << " ";
    }
    cout << endl;
    //Descending 10 to 1
    for(int i = 10; i >= 1; i--){
        cout << i << " ";
    }
    cout << endl;
    //Printing odd numbers
    for(int i = 1; i <= 19;i += 2){
        cout << i << " ";
    }
    cout << endl;
    //Printing (double) decimal numbers
    for(double i = 1; i < 2;i += 0.02){
        cout << i << endl;
    }
    cout << endl;
    //Printing (float) decimal numbers
    for(float i = 1; i < 2;i += 0.02){
        cout << i << endl;
    }

    cout << endl;
    return 0;
}
