// challenge_11.cpp

#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//Function Declarations
void integer_eqn();

int main() {
	integer_eqn();
}

//a^3 - 2b^2 +10c = d^2 - 1
void integer_eqn(){
    int count = 0;
    int sol, eqn;

    for(int d = -100;d <= 100;d++){
        for(int c = -100;c <= 100;c++){
            for(int b = -100;b <= 100;b++){
                for(int a = -100;a <= 100;a++){
                    sol = d*d-1;
                    eqn = (a*a*a)-(2*b*b)+(10*c);
                    if(sol == eqn) count++;
                }
            }
        }
    }
    cout << "Count: " << count << endl;
}