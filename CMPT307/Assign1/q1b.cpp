//*  g++ -o q1b q1b.cpp
//* ====================================================
// C++ program to compare running times of:
// Algorithm 1: 100n^2
// Algorithm 2: 2^n
// Assuming 10^6 (1,000,000) instructions per second
#include <bits/stdc++.h>
using namespace std;

//* For what minimum value of n does Algo 1 run faster than Algo 2
int main(){
    const int INSTRUCTIONS_PER_SECOND = 1000000;
	const int n = 15;

    cout << "===================================================\n";

    // algo1 calculation
    double algo1 = (100*pow(n, 2)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 1 (100n^2) ran in " << algo1 << " seconds with an n=" << n << endl;

    // algo1 calculation
    double algo2 = (pow(2, n)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 2 (2^n) ran in " << algo2 << " seconds with an n=" << n << endl;

    cout << "===================================================\n";

    // showing which is slower
    if(algo1 == algo2){
        cout << "Both ran in the same time" << endl;
    } else if (algo1 > algo2) {
        cout << "Algorithm 2 (2^n) was faster by " << algo1-algo2 << endl;
    } else {
        cout << "Algorithm 1 (100n^2) was faster by " << algo2-algo1 << endl;
    }

    cout << "===================================================\n";

	return 0;
}
