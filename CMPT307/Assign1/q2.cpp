//*  g++ -o q2 q2.cpp
//* ====================================================
// Program to find largest input n for which to following algorithm running times are under an hour
// Algorithm 1: n^2
// Algorithm 2: n^3
// Algorithm 3: 100n^2
// Algorithm 4: nlogn
// Algorithm 5: 2^n
// Algorithm 6: 2^(2^n)
// Assuming 10^10 (10000000000) instructions per second (ten billion)
#include <bits/stdc++.h>
using namespace std;

//* For what minimum value of n does Algo 1 run faster than Algo 2
int main(){
    const long long INSTRUCTIONS_PER_SECOND = 10000000000;
    const int SECONDS_IN_HOUR = 3600;
	const long long n = 906000000000; // 906 billion

    cout << "===================================================\n";

    // algo1 calculation: n=6000000
    double algo1 = (pow(n, 2)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 1 (n^2) ran in " << algo1 << " seconds with an n=" << n << endl;

    // algo2 calculation: n=33019
    double algo2 = (pow(n, 3)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 2 (n^3) ran in " << algo2 << " seconds with an n=" << n << endl;

    // algo3 calculation: n=600000
    double algo3 = (100*pow(n, 2)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 3 (100n^2) ran in " << algo3 << " seconds with an n=" << n << endl;

    // algo4 calculation: n= ~906316000000 (~906 billion)
    double algo4 = (n*log2(n)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 4 (nlogn) ran in " << algo4 << " seconds with an n=" << n << endl;

    // algo5 calculation: n=45
    double algo5 = (pow(2, n)) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 5 (2^n) ran in " << algo5 << " seconds with an n=" << n << endl;

    // algo6 calculation: n=5
    double algo6 = (pow(2, pow(2, n))) / INSTRUCTIONS_PER_SECOND;
    cout << "Algorithm 6 (2^(2^n)) ran in " << algo6 << " seconds with an n=" << n << endl;

    cout << "===================================================\n";
	return 0;
}