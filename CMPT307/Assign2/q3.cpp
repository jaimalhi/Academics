//*  g++ -o x q3.cpp

#include <bits/stdc++.h>
using namespace std;

int main(){
	const long long n = 1000; 
    const int k = 1;

    cout << "===================================================\n";

    double operations = (n*k + n*log2(n/k));
    cout << operations << " operations with n=" << n << " and k=" << k << endl;

    cout << "===================================================\n";
    
	return 0;
}