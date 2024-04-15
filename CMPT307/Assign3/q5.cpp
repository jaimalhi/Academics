//* g++ -o x q5.cpp

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <climits>
using namespace std;

//* Implement the following algorithms for the rod-cutting problem and 
//* compare their running times for n = 5, 10, 15, 20, 25, 30, respectively
// Cut-Rod(p, n) (slide page 4)
// Memoized-Cut-Rod(p, n) (slide page 6)
// Bottom-Up-Rod(p, n) (slide page 7)

// ======================================== Cut Rod ========================================
// Parameters: prices p, length n; 
// Return value: maximum revenue
int CutRod(const vector<int>& p, int n) {
    if (n == 0) return 0;

    int q = INT_MIN; // Represent negative infinity
    
    for (int i = 1; i <= n; ++i) {
        q = std::max(q, p[i] + CutRod(p, n - i));
    }

    return q;
}

// ==================================== Memoized Cut Rod ====================================
// Parameters: prices p, length n;
// Return value: maximum revenue
int MemoizedCutRodAux(const vector<int>& p, int n, vector<int>& r) {
    // This is helper function for MemoizedCutRod
    if (r[n] >= 0) return r[n];
    
    int q;
    if (n == 0) {
        q = 0;
    } else {
        q = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            q = std::max(q, p[i] + MemoizedCutRodAux(p, n - i, r));
        }
    }

    r[n] = q;
    return q;
}

// Parameters: prices p, length n;
// Return value: maximum revenue
int MemoizedCutRod(const vector<int>& p, int n) {
    vector<int> r(n + 1, INT_MIN);
    return MemoizedCutRodAux(p, n, r);
}

// ==================================== Bottom Up Cut Rod ====================================
// Parameters: prices p, length n;
// Return value: maximum revenue
int BottomUpCutRod(const vector<int>& p, int n) {
    vector<int> r(n + 1, 0);
    for (int j = 1; j <= n; ++j) {
        int q = INT_MIN;
        for (int i = 1; i <= j; ++i) {
            q = std::max(q, p[i] + r[j - i]);
        }
        r[j] = q;
    }
    return r[n];
}

// ======================================== Main Function ========================================
void ReportRunningTimes(const std::vector<int>& p, const std::vector<int>& rod_lengths) {
    for (int n : rod_lengths) {
        cout << "==================== n = " << n << " ====================" << endl;
        auto start = std::chrono::high_resolution_clock::now();
        CutRod(p, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "CutRod for n = " << n << " took " << duration << " nanoseconds.\n";

        start = std::chrono::high_resolution_clock::now();
        MemoizedCutRod(p, n);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "MemoizedCutRod for n = " << n << " took " << duration << " nanoseconds.\n";

        start = std::chrono::high_resolution_clock::now();
        BottomUpCutRod(p, n);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "BottomUpCutRod for n = " << n << " took " << duration << " nanoseconds.\n";
    }
}

int main() {
    vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30,            // Prices for rods of length 1 to 10
                            35, 40, 45, 50, 55, 60, 65, 70, 75, 80,         // Prices for rods of length 11 to 20
                            85, 90, 95, 100, 105, 110, 115, 120, 125, 130}; // Prices for rods of length 21 to 30

    vector<int> rod_lengths = {5, 10, 15, 20, 25, 30};

    ReportRunningTimes(prices, rod_lengths);

    return 0;
}